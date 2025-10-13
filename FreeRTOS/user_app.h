#ifndef USER_APP_H
#define	USER_APP_H

#define EXAMPLE_1   0
#define FILOSOFOS   1

#if EXAMPLE_1 == 1

void config_user_app();
void task_1();
void task_2();

#elif FILOSOFOS == 1

void config_user_app();
void f_0();
void f_1();
void f_2();
void f_3();
void f_4();

void pensar();
void comer(int f_id);

#endif

#endif	/* USER_APP_H */

