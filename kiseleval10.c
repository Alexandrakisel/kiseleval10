#include <stdio.h>
#include <locale.h>
#include <math.h>

void z1();
void z2();
void dz();

double F1(double x);
double F2(double x);
double acos_n(double x, int N);
double acos_eps(double x, double eps);

float area_triangle(float a, float h);
void show_definition();
void draw_triangle(char c, int a);
int get_side();
void compare_triangles(float a1, float h1, float a2, float h2);

const double PI = 3.14159265358979324;

int main() {
	setlocale(LC_CTYPE, "Rus");

	printf("Задание 1\n\n");
	z1();

	printf("\nЗадание 2\n\n");
	z2();

	printf("\nДЗ\n\n");
	dz();

	return 0;
}

double F1(double x) {
	if (x <= 3)
		return x * x - 3 * x + 9;
	return 1.0 / (x * x * x + 3);
}

double F2(double x) {
	return x * exp(sin(x * x));
}

void z1() {
	double x;
	int choice;

	printf("Введите x: ");
	scanf("%lf", &x);
	printf("F1(x) = %lf, F2(x) = %lf\n\n", F1(x), F2(x));

	printf("Меню:\n");
	printf("1 - значение F1(x)\n");
	printf("2 - значение F2(x)\n");
	printf("3 - произведение F1(x)*F2(x)\n");
	printf("4 - разность квадратов F1^2 - F2^2\n");
	printf("5 - удвоенная сумма 2*(F1 + F2)\n");
	printf("Ваш выбор: ");
	scanf("%d", &choice);

	switch (choice) {
	case 1:
		printf("F1(%lf) = %lf\n", x, F1(x));
		break;
	case 2:
		printf("F2(%lf) = %lf\n", x, F2(x));
		break;
	case 3:
		printf("произведение = %lf\n", F1(x) * F2(x));
		break;
	case 4:
		printf("разность квадратов = %lf\n", F1(x) * F1(x) - F2(x) * F2(x));
		break;
	case 5:
		printf("удвоенная сумма = %lf\n", 2.0 * (F1(x) + F2(x)));
		break;
	default:
		printf("Нет такого пункта меню\n");
	}
}

double acos_n(double x, int N) {
	double sum = 0, term = x;
	int k;

	for (k = 0; k < N; k++) {
		sum += term;
		term *= x * x * (2.0 * k + 1) * (2.0 * k + 1) / ((2.0 * k + 2) * (2.0 * k + 3));
	}
	return PI / 2 - sum;
}

double acos_eps(double x, double eps) {
	double sum = 0, term = x;
	int k = 0;

	while (term >= eps) {
		sum += term;
		k++;
		term *= x * x * (2.0 * k + 1) * (2.0 * k + 1) / ((2.0 * k + 2) * (2.0 * k + 3));
	}
	return PI / 2 - sum;
}

void z2() {
	double x, eps;
	int N, k;

	printf("Введите x (|x| < 1): ");
	scanf("%lf", &x);

	if (x <= -1 || x >= 1) {
		printf("Ряд сходится только при |x| < 1\n");
		return;
	}

	printf("Введите число членов ряда N: ");
	scanf("%d", &N);
	printf("Введите точность eps: ");
	scanf("%lf", &eps);

	printf("\n|  N |  acos_n(x) |   отклонение\n");
	printf("-----------------------------------\n");
	for (k = 1; k <= 18; k++)
		printf("| %2d | %10.7f | %12.3e\n", k, acos_n(x, k), fabs(acos(x) - acos_n(x, k)));

	printf("\nСравнение результатов:\n");
	printf("Библиотечный acos(x): %lf\n", acos(x));
	printf("acos_n(x, %d):         %lf\n", N, acos_n(x, N));
	printf("acos_eps(x, eps):     %lf\n", acos_eps(x, eps));
	printf("Отклонение acos_n:   %le\n", fabs(acos(x) - acos_n(x, N)));
	printf("Отклонение acos_eps: %le\n", fabs(acos(x) - acos_eps(x, eps)));
}

float area_triangle(float a, float h) {
	return 0.5f * a * h;
}

void show_definition() {
	printf("Треугольник - фигура, образованная тремя точками,\n");
	printf("не лежащими на одной прямой, и тремя отрезками,\n");
	printf("попарно соединяющими эти точки.\n");
}

void draw_triangle(char c, int a) {
	int i, j;

	for (i = 0; i < a; i++) {
		for (j = 0; j < a - 1 - i; j++)
			printf(" ");
		if (i == 0)
			printf("%c", c);
		else if (i == a - 1)
			for (j = 0; j < 2 * a - 1; j++)
				printf("%c", c);
		else {
			printf("%c", c);
			for (j = 0; j < 2 * i - 1; j++)
				printf(" ");
			printf("%c", c);
		}
		printf("\n");
	}
}

int get_side() {
	int a;
	printf("Введите сторону треугольника: ");
	scanf("%d", &a);
	return a;
}

void compare_triangles(float a1, float h1, float a2, float h2) {
	float s1 = area_triangle(a1, h1);
	float s2 = area_triangle(a2, h2);

	if (s1 > s2)
		printf("Первый треугольник больше на %f\n", s1 - s2);
	else if (s2 > s1)
		printf("Второй треугольник больше на %f\n", s2 - s1);
	else
		printf("Треугольники равны по площади\n");
}

void dz() {
	int choice, a;
	float h, a1, h1, a2, h2;

	while (1) {
		printf("\nМеню:\n");
		printf("1 - рассчитать площадь\n");
		printf("2 - вывести определение фигуры\n");
		printf("3 - нарисовать фигуру\n");
		printf("4 - ввести параметры (сторона и высота)\n");
		printf("5 - сравнить два треугольника по площади\n");
		printf("0 - выход\n");
		printf("Ваш выбор: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			a = get_side();
			printf("Введите высоту: ");
			scanf("%f", &h);
			printf("Площадь = %f\n", area_triangle((float)a, h));
			break;
		case 2:
			show_definition();
			break;
		case 3:
			a = get_side();
			printf("Каким символом рисовать: ");
			while (getchar() != '\n');
			draw_triangle((char)getchar(), a);
			break;
		case 4:
			a = get_side();
			printf("Введите высоту: ");
			scanf("%f", &h);
			printf("Текущие параметры: сторона %d, высота %f\n", a, h);
			break;
		case 5:
			printf("Первый треугольник:\n");
			a = get_side();
			printf("Введите высоту: ");
			scanf("%f", &h1);
			a1 = (float)a;
			printf("Второй треугольник:\n");
			a = get_side();
			printf("Введите высоту: ");
			scanf("%f", &h2);
			a2 = (float)a;
			compare_triangles(a1, h1, a2, h2);
			break;
		case 0:
			return;
		default:
			printf("Нет такого пункта меню\n");
		}
	}
}
