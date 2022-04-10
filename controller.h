#ifndef CONTROLLER_H
#define CONTROLLER_H


class Controller {
	private:
		float P;
		float I;
		float D;
		bool add_steady; // idea behind this is to make it easier to reach the steady state using an approximate model of the steady state such that reference_ss ~ pwm_ss
		float area;
		float cache_error;
		unsigned long cache_time;
	public:
		Controller(float P = 1, float I = 1, float D = 1, bool add_steady = true):P(P), I(I), D(D), add_steady(add_steady) {
			area = 0;
			cache_error = 0;
			cache_time = micros();
		}
		int getSteady(int reference){
			return 50;
		}
		float _p(int error, int reference, bool _add_steady) {
			return P * error + _add_steady * getSteady(reference);
		}
		float _i(int error, int cache_error, float delta_t) {
			area += (cache_error + error) * delta_t / 2;
			return I * area;
		}
		float _d(int error, int cache_error, float delta_t) {
			return D * (error - cache_error) / delta_t;
		}
		int pid(int speed, int reference){
			int error = reference - speed;
			unsigned long cur_time = micros();
			float delta_t = (float)(cur_time - cache_time) / 1000000.;
			float p = _p(error, reference, add_steady);
			float i = _i(error, cache_error, delta_t);
			float d = _d(error, cache_error, delta_t);
			int result = p + i + d;
			cache_error = error;
			cache_time = cur_time;
			return round(result);
		}
};







#endif
