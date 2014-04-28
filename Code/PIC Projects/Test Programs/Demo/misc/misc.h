// misc.c header file


void CP0Init(void);
void INTInitialize(void);
void wait(int num);
void SetupButtons(void);
void SetupIO(void);
int CheckButtons(void);
double CalculateVoltage(int an1);
void IncPWMDutyCycle(int num, double perc, int dir);
void SetPWMDutyCycle(int num,double perc);

