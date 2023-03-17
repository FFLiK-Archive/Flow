#pragma once
enum TransitionType { LINEAR, IN_SINE, OUT_SINE, IN_OUT_SINE, IN_QUAD, OUT_QUAD, IN_OUT_QUAD, IN_QUINT, OUT_QUINT, IN_OUT_QUINT, IN_EXPO, OUT_EXPO, IN_OUT_EXPO };

class Transition {
private:
	double Calculate(double progress, TransitionType type);

public:
	
};

