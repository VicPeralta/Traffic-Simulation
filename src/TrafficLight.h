#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "TrafficObject.h"
#include <condition_variable>
#include <deque>
#include <mutex>
#include <random>
// forward declarations to avoid include cycle
class Vehicle;

// FP.3 Define a class „MessageQueue“ which has the public methods send and
// receive. Send should take an rvalue reference of type TrafficLightPhase
// whereas receive should return this type. Also, the class should define an
// std::dequeue called _queue, which stores objects of type TrafficLightPhase.
// Also, there should be an std::condition_variable as well as an std::mutex as
// private members.

template <class T> class MessageQueue {
public:
  void send(T &&message);
  T receive();
private:
  std::deque<T> _queue;
  std::mutex m_mutex;
  std::condition_variable m_conVariable;
  bool m_dataReady = false;
};

// FP.1 : Define a class „TrafficLight“ which is a child class of TrafficObject.
// The class shall have the public methods „void waitForGreen()“ and „void
// simulate()“ as well as „TrafficLightPhase getCurrentPhase()“, where
// TrafficLightPhase is an enum that can be either „red“ or „green“. Also, add
// the private method „void cycleThroughPhases()“. Furthermore, there shall be
// the private member _currentPhase which can take „red“ or „green“ as its
// value.

enum class TrafficLightPhase { red, green };

class TrafficLight : public TrafficObject {
public:
  // constructor / desctructor
  TrafficLight() : m_eng(m_rd()), m_distr(4, 6), _currentPhase(TrafficLightPhase::red) {}
  // getters / setters
  // typical behaviour methods
  void waitForGreen();
  void simulate();
  TrafficLightPhase getCurrentPhase();
private:
  std::random_device m_rd;
  std::mt19937 m_eng;
  std::uniform_int_distribution<> m_distr;
  bool m_dataReady = false;
  TrafficLightPhase _currentPhase;
  // typical behaviour methods
  void cycleThroughPhases();
  // FP.4b : create a private member of type MessageQueue for messages of type
  // TrafficLightPhase and use it within the infinite loop to push each new
  // TrafficLightPhase into it by calling send in conjunction with move
  // semantics.
  MessageQueue<TrafficLightPhase> _messageQueue;
  std::condition_variable _condition;
  std::mutex _mutex;
};

#endif