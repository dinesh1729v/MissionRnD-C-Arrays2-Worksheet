/*
OVERVIEW: You are given a bank statement where transactions are ordered by date. Write a function that finds the number of transactions in that statement after a given date.
-- find the count of numbers greater than a given number in a sorted array.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
date = "19-10-2004"
Output: 1 (as there is only one transaction { 30, "03-03-2005", "Third" })

INPUTS: One bank statement (array of transactions) and date.

OUTPUT: Return the number of transactions in that statement after a given date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/
#include<stdio.h>
#include<stdlib.h>
struct transaction {
	int amount;
	char date[11];
	char description[20];
};
int length1(char *s)
{
	int i = 0;
	for (i = 0; s[i] != '\0'; i++);
	return i;
}
int isValid1(char *s)
{
	int d, i, m, y, month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }, leap = 0;
	if (length1(s) != 10)return 0;
	for (i = 0; i<10; i++)
	{
		if (i == 2 || i == 5)continue;
		if ((s[i] - 48)<0 || (s[i] - 48)>9)return 0;
	}
	if (s[2] != '-' || s[5] != '-')
		return 0;
	d = (s[0] - 48) * 10 + (s[1] - 48);
	m = (s[3] - 48) * 10 + (s[4] - 48);
	y = ((s[6] - 48) * 1000) + ((s[7] - 48) * 100) + ((s[8] - 48) * 10) + ((s[9] - 48));
	if (y == 0)return 0;
	if (y % 4 == 0)leap = 1;
	if ((y % 100 == 0) && (y % 400 != 0))leap = 0;
	if (d <= 0 || d>31)return 0;
	if (m <= 0 || m>12)return 0;
	if (m == 2 && d > 29)return 0;
	if (m == 2 && leap == 1 && d <= 29)return 1;
	if (month[m - 1] < d)return 0;
	return 1;
}
int countGreaterNumbers(struct transaction *Arr, int len, char *date) {
	if (!isValid1(date) || Arr == NULL || len < 0)return NULL;
	int cnt=0,i;
	int d1, d2, m1, m2, y1, y2;
	d1 = (date[0] - 48) * 10 + (date[1] - 48);
	m1 = (date[3] - 48) * 10 + (date[4] - 48);
	y1 = (date[6] - 48) * 1000 + (date[7] - 48) * 100 + (date[8] - 48) * 10 + (date[9] - 48);
	for (i = 0; i < len; i++)
	{
		d2 = (Arr[i].date[0] - 48) * 10 + (Arr[i].date[1] - 48);
		
		y2 = (Arr[i].date[6] - 48) * 1000 + (Arr[i].date[7] - 48) * 100 + (Arr[i].date[8] - 48) * 10 + (Arr[i].date[9] - 48);
		if (y2 < y1)continue;
		m2 = (Arr[i].date[3] - 48) * 10 + (Arr[i].date[4] - 48);
		if ((y2 == y1) && (m2 < m1))continue;
		d2 = (Arr[i].date[0] - 48) * 10 + (Arr[i].date[1] - 48);
		if ((y2 == y1) && (m2 == m1) && (d2 <= d1))continue;
		break;
	}
	return len-i;
}
