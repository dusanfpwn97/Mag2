#pragma once



namespace efe
{
	class FpsLimiter
	{
	public:

		FpsLimiter();
		~FpsLimiter();


		void init(float maxFPS);
		void setMaxFPS(float maxFPS);
		void beginFrame();

		
		float end(); //returns fps;

	private:
		void calculateFPS();

		unsigned int _startTicks;


		float _fps;
		float _frameTime;
		float _maxFPS;

	};



}