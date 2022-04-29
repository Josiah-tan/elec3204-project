#ifndef CONTROLLER_H
#define CONTROLLER_H


class Controller {
	/* 
	 * class: PID controller system
	 * parameters:
	 *  -- P: proportional control parameter (default = 1)
	 *  -- I: integral control parameter (default = 1)
	 *  -- D: differential control parameter (default = 1)
	 *  -- add_steady: true - add in an approximation model that roughly estimates the steady state output; false - do not add in this model (default = true)
	 */
	private:
		float P;
		float I;
		float D;
		bool add_steady;
		float area; // cache area for integral control
		float cache_error; // cache error for integral and differential control
		unsigned long cache_time; // cache time for integral and differential control
	public:
		Controller(float P = 1, float I = 1, float D = 1, bool add_steady = true):P(P), I(I), D(D), add_steady(add_steady) {
			area = 0; // initialize the area to 0
			cache_error = 0; // initialize the error to zero
			cache_time = micros(); // set the initial time to be the Initialization time
		}
		int getSteady(int reference){
			/*
			 * function: steady state estimator
			 * parameters:
			 *  -- reference: the reference speed to achieve
			 * returns:
			 *  -- steady state pwm
			 */
			return 50 + reference / 2;
		}
		float _p(int error, int reference, bool _add_steady) {
			/*
			 * function: proportional controller estimator
			 * parameters:
			 *  -- error: the error between the reference and the actual value
			 *  -- reference: the reference value to achieve
			 *  -- _add_steady: true - add in an approximation model that roughly estimates the steady state output; false - do not add in this model (default = true)
			 */
			return P * error + _add_steady * getSteady(reference);
		}
		float _i(int error, int cache_error, float delta_t) {
			/*
			 * function: integral controller estimator
			 * parameters:
			 *  -- error: the error between the reference and the actual value
			 *  -- cache_error: cached error from previous function call
			 *  -- delta_t: time between last function call and this call
			 */
			area += (cache_error + error) * delta_t / 2;
			area = constrain(area, -5, 5); // constrain the area to ensure saturation doesn't occur
			return I * area;
		}
		float _d(int error, int cache_error, float delta_t) {
			/*
			 * function: differential controller estimator
			 * parameters:
			 *  -- error: the error between the reference and the actual value
			 *  -- cache_error: cached error from previous function call
			 *  -- delta_t: time between last function call and this call
			 */
			return D * (error - cache_error) / delta_t;
		}
		int pid(int speed, int reference){
			/*  
			 * function: apply PID control
			 * parameters:
			 *  -- speed: current measured speed
			 *  -- reference: the speed desired
			 */
			int error = reference - speed;
			unsigned long cur_time = micros();
			float delta_t = (float)(cur_time - cache_time) / 1000000.; // convert to seconds
			float p = _p(error, reference, add_steady);
			float i = _i(error, cache_error, delta_t);
			float d = _d(error, cache_error, delta_t);
			// print out important PID information for graphing
			Serial.print("i: ");
			Serial.println(i);
			Serial.print("p: ");
			Serial.println(p);
			Serial.print("d: ");
			Serial.println(d);
			// evaluate PID
			int result = p + i + d;
			// cache results
			cache_error = error;
			cache_time = cur_time;
			// return PID as integer (as required)
			return round(result);
		}
};







#endif
