#include "Transition.h"
#include <cmath>

#define PI 3.141592653

double Transition::Calculate(double progress, TransitionType type) {
	double result = 0;
	switch (type) {
	case LINEAR:
		result = progress;
		break;
	case IN_SINE:
		result = 1 - cos(progress * PI / 2);
		break;
	case OUT_SINE:
		result = sin(progress * PI / 2);
		break;
	case IN_OUT_SINE:
		result =  -(cos(PI * progress) - 1) / 2;
		break;
	case IN_QUAD:
		result = progress * progress;
		break;
	case OUT_QUAD:
		result = 1 - (1 - progress) * (1 - progress);
		break;
	case IN_OUT_QUAD:
		result = progress < 0.5 ? 2 * progress * progress : 1 - pow(-2 * progress + 2, 2) / 2;
		break;
	case IN_QUINT:
		result = progress * progress * progress * progress;
		break;
	case OUT_QUINT:
		result = 1 - pow(1 - progress, 5);
		break;
	case IN_OUT_QUINT:
		result = progress < 0.5 ? 16 * progress * progress * progress * progress * progress  : 1 - pow(-2 * progress + 2, 5) / 2;
		break;
	case IN_EXPO:
		result = progress == 0 ? 0 : pow(2, 10 * progress - 10);
		break;
	case OUT_EXPO:
		result = progress == 1 ? 1 : 1 - pow(2, -10 * progress);
		break;
	case IN_OUT_EXPO:
		result = progress == 0 ? 0 : progress == 1 ? 1 : progress < 0.5 ? pow(2, 20 * progress - 10) / 2 : (2 - pow(2, -20 * progress + 10)) / 2;
	}
	if (progress == 1) {
		result = 1;
	}
	return result;
}
