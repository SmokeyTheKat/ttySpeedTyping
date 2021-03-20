#include <ddcDef.h>
#include <ddcString.h>
#include <ddcPrint.h>
#include <ddcColors.h>
#include <ddcKeyboard.h>

struct text
{
	char* title;
	char* text;
};

#include "./texts.h"

#define CGRAY "\x1b[38;2;120;120;120m"

void run(struct text text)
{
	cursor_clear();
	cursor_home();
	cursor_move(0,4);

	ddPrintf(CGRAY"%s\r"CGRAY, text.text);

	char key = 1;
	int pos = 0;

	long textlen = cstring_length(text.text);

	char* buf = malloc(textlen);
	bool wrong = -1;

	while ((key = ddKey_getch_noesc()))
	{
		if (key == DDK_BACKSPACE)
		{
			if (pos == 0) continue;
			cursor_left();
			ddPrintf(CGRAY"%c", text.text[pos-1]);
			cursor_left();
			pos--;
			if (pos == wrong)
				wrong = -1;
			continue; 
		}
		if (pos == textlen) continue;
		buf[pos] = key;
		if (wrong != -1 || buf[pos] != text.text[pos])
		{
			ddPrintf(CRED);
			if (wrong == -1)
				wrong = pos; 
			if (text.text[pos] == ' ')
			{
				ddPrints("\x1b[7m");
			}
		}
		else
		{
			ddPrintf(CGREEN);
		}
		ddPrint_char(text.text[pos]);
		ddPrints("\x1b[0m");
		pos++;
		if (pos == textlen && wrong == -1)
			break;
	}

	cursor_move_to(0,20);

	ddPrints(CGREEN"GOOD :)\n");
}

int main(void)
{
	srand(time(0));
	while (1)
	{
		run(texts[(rand()%(sizeof(texts)/(sizeof(struct text))))]);
	}
	return 0;
}














