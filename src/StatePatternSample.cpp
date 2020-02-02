#include <iostream>

class SwitchState {
  friend class Switch;
public:
  virtual SwitchState* push() =0;

protected:
  static SwitchState* on_state();
  static SwitchState* off_state();
};

class OffState : public SwitchState {
public:
  SwitchState* push() override;
};

class OnState : public SwitchState {
public:
  SwitchState* push() override;
};

// OFF状態でボタン押したらON
SwitchState* OffState::push() {
  std::cout << "-> ON" << std::endl;
  return SwitchState::on_state();
}

// ON状態でボタン押したらOFF
SwitchState* OnState::push() {
  std::cout << "-> OFF" << std::endl;
  return SwitchState::off_state();
}

SwitchState* SwitchState::on_state() {
  static OnState state;
  return &state;
}

SwitchState* SwitchState::off_state() {
  static OffState state;
  return &state;
}

class Switch {
public:
  Switch() : state_(SwitchState::off_state()) {}
  void push() {
    // 現stateでpush()し、新たなstateに遷移する
    state_ = state_->push();
  }
private:
  SwitchState* state_;
};

int main() {
  Switch sw;
  for(int i=0; i<=1000000; i++)
  {
    sw.push();
  }
};