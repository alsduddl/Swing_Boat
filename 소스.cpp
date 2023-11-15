#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define SERVO 6

#define sw1 0
#define sw2 1
#define led1 4
#define led2 5

int main(void)
{
	if (wiringPiSetup() == -1)
	{
		return 1;
	}

	pinMode(SERVO, OUTPUT);
	softPwmCreate(SERVO, 0, 200);

	pinMode(sw1, INPUT);
	pinMode(sw2, INPUT);
	pinMode(led1, OUTPUT);
	pinMode(led2, OUTPUT);
	int current = 15;                                   //0µµ
	digitalWrite(led1, LOW);
	digitalWrite(led2, LOW);

	while (1)
	{

		if (digitalRead(sw1) == HIGH)
		{
			digitalWrite(led1, HIGH);
			digitalWrite(led2, LOW);

			while (1) {
				for (current; current <= 24; current += 2) {           //90µµ
					softPwmWrite(SERVO, current);
					delay(200);
				}

				for (current; current > 5; current -= 2) {           //-90µµ
					softPwmWrite(SERVO, current);
					delay(200);
				}
				if (digitalRead(sw2) == HIGH) {
					digitalWrite(led1, LOW);
					digitalWrite(led2, HIGH);

					break;
					delay(800);
				}
			}
		}

	}
	return 0;
}
