#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <conio.h>

#define EPS 0.000001

float func(float x) {
	float one = -10 * (pow((x - 30), 5));
	float two = 12 * (pow(x, 4));
	float three = -3 * (pow(x, 6));
	float four = (pow(x, 3)) * 5;
	float five = -10;
	float res1 = one + two + three + four + five;
	float res = res1 * (pow(10, -3));
	return res;
}

int read(double *x1, double *x2, int *n, double *delta, char *group,
		char *student) {
	printf("Opening file...\n");
	FILE *f = fopen("Input.txt", "r");
	if (f == 0) {
		printf("File can't be opened!\n");
		return -1;
	}
	printf("Opened!\n");

	fscanf(f, "%lf %lf %d %lf\n", x1, x2, n, delta);
	fscanf(f, "%[^\n]\n", group);
	fscanf(f, "%[^\n]\n", student);
	fclose(f);

	printf("Read!\n");

	return 0;
}

void write_out(FILE *f, double x1, double x2, int n, double delta) {

	fprintf(f, "***************************************************************\n");
	fprintf(f, "*X1%17.2f*X2:%17.2f*Delta:%14.2f*\n", x1, x2, delta);
	fprintf(f, "***************************************************************\n");
	int i = 1;
	while (x1 < (x2 + EPS) && i <= n) {
		fprintf(f, "|%4d|%20.2f|%20.2f|\n", i, x1, func(x1));
		fprintf(f, "|----|--------------------|--------------------|\n");
		i++;
		x1 += delta;
	}
}
void write_bin(FILE *f, double x1, double x2, int n, double delta) {
	fwrite(&n, 1, sizeof(int), f);
	int i = 1;
	while (x1 < (x2 + EPS) && i <= n) {
		fwrite(&x1, 1, sizeof(double), f);
		double r = func(x1);
		fwrite(&r, 1, sizeof(double), f);
		i++;
		x1 += delta;
	}
}

void read_bin(FILE *f) {
	int n;
	fread(&n, sizeof(int), 1, f);
	double *br = (double*) malloc(2 * n * sizeof(double));
	fread(br, sizeof(double), 2 * n, f);
	for (int i = 0; i < n; i++) {
		printf("|%4d|%20.2f|%20.2f|\n", i+1, br[2 * i], br[2 * i + 1]);
		printf("|----|--------------------|--------------------|\n");
	}
}

int main() {
	double x1;
	double x2, delta;
	int n;
	char group[50];
	char student[50];

	printf("Hello!");
	read(&x1, &x2, &n, &delta, group, student);

	printf("%lf\n%lf\n%u\n%lf\n%s\n%s\n", x1, x2, n, delta, group, student);

	FILE *fa = fopen("Output.txt", "w");
	write_out(fa, x1, x2, n, delta);
	fprintf(fa, "%s\n", group);
	fprintf(fa, "%s\n", student);
	fclose(fa);

	FILE *fb = fopen("Output.bin", "wb");
	write_bin(fb, x1, x2, n, delta);
	fclose(fb);

	fb = fopen("Output.bin", "rb");
	read_bin(fb);
	fclose(fb);

	return 0;
}

