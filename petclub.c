//petclub.c -- use binary search tree

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"

char menu(void);
void addpet(Tree * pt);
void droppet(Tree * pt);
void showpets(const Tree * pt);
void findpet(const Tree * pt);
void printitem(Item item);
void uppercase(char * str);
char * s_gets(char * st, int n);

int main(void)
{
	Tree pets;
	char choice;

	InitializeTree(&pets);
	while ((choice = menu()) != 'q')
	{
		switch (choice)
		{
			case 'a' : addpet(&pets);
				break;
			case 'l' : showpets(&pets);
				break;
			case 'f' : findpet(&pets);
				break;
			case 'n' : printf("%d pets in club\n", TreeItemCount(&pets));
				break;
			case 'd' : droppet(&pets);
				break;
			default : puts("Error in switch");
		}
	}
	DeleteAll(&pets);
	puts("Executed.");

	return 0;
}

char menu(void)
{
	int ch;
	puts("Nerfville Pet Club");
	puts("Enter 'char' and action below:");
	puts("a) add pet         l) show pets list");
	puts("n) amount of pet   f) find a pet");
	puts("d) delete pet      q) exit");
	while ((ch = getchar()) != EOF)
	{
		while (getchar() != '\n')
			continue;
		ch = tolower(ch);
		if (strchr("alfndq", ch) == NULL)
			puts("Enter a, l, f, n, d or q:");
		else
			break;
	}
	if (ch == EOF)
		ch = 'q';

	return ch;
}

void addpet(Tree * pt)
{
	Item temp;

	if (TreeIsFull(pt))
		puts("No place in club yet");
	else
	{
		puts("Enter pet name:");
		s_gets(temp.petname, SLEN);
		puts("Enter kind pet:");
		s_gets(temp.petkind, SLEN);
		uppercase(temp.petname);
		uppercase(temp.petkind);
		AddItem(&temp, pt);
	}
}

void showpets(const Tree * pt)
{
	if (TreeIsEmpty(pt))
		puts("No entries");
	else
		Traverse(pt, printitem);
}

void printitem(Item item)
{
	printf("Pet: %-19s  Kind: %-19s\n", item.petname, item.petkind);
}

void findpet(const Tree * pt)
{
	Item temp;

	if (TreeIsEmpty(pt))
	{
		puts("No entries");
		return;
	}
	puts("What pet name do you want to find? ");
	s_gets(temp.petname, SLEN);
	puts("Enter kind of pet");
	s_gets(temp.petkind, SLEN);
	uppercase(temp.petname);
	uppercase(temp.petkind);
	printf("%s by name %s ", temp.petkind, temp.petname);
	if (InTree(&temp, pt))
		printf("is a club member.\n");
	else
		printf("isn't a club member.\n");
}

void droppet(Tree * pt)
{
	Item temp;

	if (TreeIsEmpty(pt))
	{
		puts("No entries");
		return;
	}
	puts("What pet name do you want to drop from club?");
	s_gets(temp.petname, SLEN);
	puts("Enter kind of pet");
	s_gets(temp.petkind, SLEN);
	uppercase(temp.petname);
	uppercase(temp.petkind);
	printf("%s by name %s ", temp.petkind, temp.petname);
	if (DeleteItem(&temp, pt))
		printf("drop from club.\n");
	else
		printf("isn't a club member.\n");
}

void uppercase(char * str)
{
	while(*str)
	{
		*str = toupper(*str);
		str++;
	}
}

char * s_gets(char * st, int n)
{
	char * ret_val;
	char * find;

	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n');
		if (find)
			*find = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}