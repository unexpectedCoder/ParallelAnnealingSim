#include "optimizer.h"

#include <iostream>
#include <fstream>


using namespace std;


Optimizer::Optimizer(double (*f)(const Vals&), size_t dim, const Bounds &bnds, const Options &opt,
                     int threads_num, QObject *parent)
  : QObject(parent)
{
  if (threads_num < 1)
    throw "Error in <AnnealingOptimizer>: threads number must be > 0!";

  annealing = new Annealing(f, dim, bnds, opt);
  nThreads = threads_num;

  threads = new QThread*[nThreads];
  anns = new Annealing*[nThreads];
  for (int i = 0; i < nThreads; ++i)
  {
    threads[i] = new QThread;
    anns[i] = new Annealing(*annealing);
    anns[i]->moveToThread(threads[i]);

    connect(threads[i], &QThread::started, anns[i], &Annealing::anneal);
    connect(anns[i], &Annealing::resultReady, this, &Optimizer::addResult);
    connect(this, &Optimizer::resultAdded, threads[i], &QThread::quit);
    connect(threads[i], &QThread::finished, anns[i], &Annealing::deleteLater);
  }
}


Optimizer::~Optimizer()
{
  for (int i = 0; i < nThreads; ++i)
  {
    threads[i]->quit();
    threads[i]->wait();
  }
  delete [] anns;
  delete [] threads;
}


void Optimizer::optimize()
{
  for (int i = 0; i < nThreads; ++i)
    threads[i]->start();
}


void Optimizer::showBestResut()
{
  cout << "\nBest optimization result:\n" << result << endl;
  emit completed(result);
}


void Optimizer::addResult(const Result &r)
{
  mutex.lock();

  results.push_back(r);
  emit resultAdded();

  static int calls = 0;
  if (calls == 0)
    result = r;
  else if (result.extr > r.extr)
    result = r;
  if (++calls == nThreads)
    emit resultsReady();

  mutex.unlock();
}


void Optimizer::showResults()
{
  cout << "\nOptimization results:\n";
  int k = 0;
  for (ResultsItr_c i = results.begin(); i != results.end(); i++)
    cout << " - thread #" << ++k << ": " << *i << endl;
}
