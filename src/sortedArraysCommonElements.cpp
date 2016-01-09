/*
OVERVIEW: You are given 2 bank statements that are ordered by date. Write a function that returns dates common to both statements
(ie both statements have transactions in these dates).
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[3] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" }, { 320, "27-08-2015", "Seventh" } };
Output: { { 10, "09-10-2003", "First" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Transactions having same dates.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include <iostream>

struct transaction {
	int amount;
	char date[11];
	char description[20];
};
int length(char *s)
{
	int i = 0;
	for (i = 0; s[i] != '\0'; i++);
	return i;
}
int isValid(char *s)
{
	int d, i, m, y, month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }, leap = 0;
	if (length(s) != 10)return 0;
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
int isOlder(char *date1, char *date2) {
	int d1, d2, m1, m2, y1, y2;
	d1 = (date1[0] - 48) * 10 + (date1[1] - 48);
	m1 = (date1[3] - 48) * 10 + (date1[4] - 48);
	y1 = ((date1[6] - 48) * 1000) + ((date1[7] - 48) * 100) + ((date1[8] - 48) * 10) + ((date1[9] - 48));
	d2 = (date2[0] - 48) * 10 + (date2[1] - 48);
	m2 = (date2[3] - 48) * 10 + (date2[4] - 48);
	y2 = ((date2[6] - 48) * 1000) + ((date2[7] - 48) * 100) + ((date2[8] - 48) * 10) + ((date2[9] - 48));
	if (y1 < y2)return 1;
	else if (y1>y2)return 2;
	else if (y1 == y2)
	{
		if (m1 < m2)return 1;
		else if (m1>m2)return 2;
		else if (m1 == m2)
		{
			if (d1 < d2)return 1;
			else if (d1>d2)return 2;
			else if (d1 == d2)return 0;
		}
	}
}
struct transaction * sortedArraysCommonElements(struct transaction *A, int ALen, struct transaction *B, int BLen) {

	if (A == NULL || B == NULL || ALen < 0 || BLen < 0)return NULL;
	int len = ALen + BLen, i = 0,j=0,c=0;
	struct transaction *common = (struct transaction*)malloc(sizeof(struct transaction)*100);
	while (len--)
	{
		if (ALen == i+1 || BLen == j+1)break;
		int compare = isOlder(A[i].date, B[j].date);
		if (compare == 2)
			i++;
		else if (compare == 1)
			j++;
		else
		{
			c++;
			common[c - 1] = A[i];
		}
	}
	return common;
}