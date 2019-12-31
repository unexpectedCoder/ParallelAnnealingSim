#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include <QObject>
#include <QMutex>
#include <QThread>

#include <vector>

#include "annealing.h"


typedef std::vector<Result> Results;
typedef std::vector<Result>::const_iterator ResultsItr_c;


class Optimizer : public QObject
{
  Q_OBJECT

public:
  explicit Optimizer(double (*f)(const Vals&), int dim, const Bounds &bnds, const Options &opt,
                     int threads_num, QObject *parent = nullptr);
  ~Optimizer();

  void optimize();

private:
  Annealing *annealing;

  int nThreads;
  QMutex mutex;
  QThread **threads;
  Annealing ** anns;

  Result result;			// The best result from all threads
  Results results;		// Results from all threads

public slots:
  void addResult(const Result&);
  void showResults();
  void showBestResut();

signals:
  void resultAdded();
  void resultsReady();
  void completed(const Result&);
};

#endif // OPTIMIZER_H
