#include "TrafficLight.h"
#include <iostream>

/* Implementation of class "MessageQueue" */

template <typename T> T MessageQueue<T>::receive() {
  // FP.5a : The method receive should use std::unique_lock<std::mutex> and
  // _condition.wait()
  // to wait for and receive new messages and pull them from the queue using
  // move semantics.
  // The received object should then be returned by the receive function.
  std::unique_lock<std::mutex> lck(m_mutex);
  m_conVariable.wait(lck, [this]() { return m_dataReady; });
  T v = std::move(_queue.back());
  _queue.pop_back();
  m_dataReady = false;
  return v;
}

template <typename T> void MessageQueue<T>::send(T &&msg) {
  // FP.4a : The method send should use the mechanisms
  // std::lock_guard<std::mutex>
  // as well as _condition.notify_one() to add a new message to the queue and
  // afterwards send a notification.
  std::lock_guard<std::mutex> lck(m_mutex);
  _queue.emplace_back(std::move(msg));
  m_dataReady = true;
  m_conVariable.notify_one();
  std::this_thread::sleep_for(std::chrono::microseconds(2));
}

/* Implementation of class "TrafficLight" */

void TrafficLight::waitForGreen() {
  // FP.5b : add the implementation of the method waitForGreen, in which an
  // infinite while-loop
  // runs and repeatedly calls the receive function on the message queue.
  // Once it receives TrafficLightPhase::green, the method returns.
  while (true) {
    if (_messageQueue.receive() == TrafficLightPhase::green) {
      return;
    }
  }
}

TrafficLightPhase TrafficLight::getCurrentPhase() { return _currentPhase; }

void TrafficLight::simulate() {
  // FP.2b : Finally, the private method „cycleThroughPhases“ should be
  // started in a thread when the public method „simulate“ is called. To do
  // this, use
  // the thread queue in the base class.
  
  threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases() {
  // FP.2a : Implement the function with an infinite loop that measures the time
  // between two loop cycles and toggles the current phase of the traffic light
  // between red and green and sends an update method to the message queue using
  // move semantics. The cycle duration should be a random value between 4 and 6
  // seconds. Also, the while-loop should use std::this_thread::sleep_for to
  // wait 1ms between two cycles.
  auto initialTime = std::chrono::high_resolution_clock::now();
  std::chrono::seconds nextCycleDuration = std::chrono::seconds(m_distr(m_eng));

  TrafficLightPhase message = _currentPhase;
  _messageQueue.send(std::move(message));
  while (true) {
    auto t = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::high_resolution_clock::now() - initialTime);
    if (t >= nextCycleDuration) {
      _currentPhase = (_currentPhase == TrafficLightPhase::green)
                          ? TrafficLightPhase::red
                          : TrafficLightPhase::green;
      message = _currentPhase;
      _messageQueue.send(std::move(message));
      nextCycleDuration = std::chrono::seconds(m_distr(m_eng));
      initialTime = std::chrono::high_resolution_clock::now();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}
