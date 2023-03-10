/*
 * Doc: calc.c
 * Explanation: a real calculator engine depending on math rules (e.g first calc
 * powers) Author: KoBruhh Date: 29.01.2023 Extra: I am coding this from a
 * mobile phone so it is kinda wierd.
 * */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

const char symb_list[] = {'+', '-', '/', '*', '^', '(', ')'};

void get_input(char* buff);
double calc(char* eq);
double single(char* ex);

/*int main() {*/
  /*char eq[100] = {0};*/
  /*do {*/
     /*3x(4+7-1)x2-2/2 */
    /*printf("Eq: ");*/
    /*get_input(eq);*/
    /*double res = calc(eq);*/
    /*printf("Result: %lf\n", res);*/
     /*double sres = single("1234*5678");*/
  /*} while (1);*/
  /*return 0;*/
/*}*/

void parse(char* eq, char* res);
double calculate(char* eq);

double calc(char* eq) {
  /* this has to obey math rules
   * first calculate powers,
   * next parantheses,
   * then multiplication and division (right to left)
   * last addition and substraction (" ")
   * */
  //	char parsed[100] = { 0 };
  //	//parsed = parse(eq);
  //	parse(eq, parsed);
  //	printf("\nparsed: %s\n", eq);
  double res = calculate("1/2/3+4*5*6");  // 2 -> (1*2)-(3/3)+1
  printf("\ncalc in: %lf\n", res);
  return 0;
}

static int idx = 0;
void parse(char* eq, char* res) {
  // char buff[];
  //  1(2(3)4)5
  int brac = 0;
  int seg = 0;
  bool first = true;
  int len = strlen(eq);
  for (int i = 0; i < len; i++) {
    if (eq[i] == '(') {
      brac++;
      seg = i;  // index of our last opening brace
      printf("\nsegment: %i\n", seg);
    }

    // xxx(???
    //		if(brac >= 1 && first) // if in the first brace
    //		{
    //			for (int k = 0; k<i; k++){
    //				res[idx] =  eq[k];
    //				idx++;
    //			}
    //			first = false;
    //		}
    // some(another(stuff)here)now
    if (eq[i] == ')') {
      /* now we can say that from seg to i,
       * it was inside of braces*/
      brac--;
      for (int j = seg + 1; j < i; j++) {
        res[idx] = eq[j];
        eq[j - 1] = ' '; // CHANGED !!! _ -> ' '
        idx++;
      }
      eq[i - 1] = ' ';
      eq[i] = ' ';  // getting rid of the "?)"

      double calc = calculate(res);
      printf("\ninner clac:%lf", calc);
      parse(eq, res);
      idx = 0;
      return;
      // return parse(res);
      // printf("\n");
    }
    //		if(!first && brac == 0) // this leads error in case of: ()()
    //			{
    //				for(int j=i+1;j<len;j++){
    //					printf("%c", eq[i]);
    //				}
    //			}
  }
  //	if(brac%2 != 0) {
  //		printf("please enter a valid equation!\n");
  //	}
  printf("\n%s", res);
  // return res;
}
char list[] = {'/', '*', '+', '-'};
int list_len = 4;

int find_next_symbol(int start, char* eq);

double calculate(char* eq) {  // especially this fn dont have to parse braces
  /* 3*5-2/2+1-3 */
  // first check for multiplication and division
  // and addition substraction
  int len = strlen(eq);
  int last_symb = -1;  // no symbol by start so indx starts from 0
  int next = -1;
  char buff[100];

  for (int i = 0; i < len; i++) {
    for (int j = i + 1; j < len;
         j++) {  // This will be replaced by find_next_symbol
      // if any symbol it is next
      for (int k = 0; k < sizeof(list) / sizeof(char); k++) {
        if (eq[j] == list[k]) {
          next = j;  //
          goto evalmd;
        }
      }
    }
    next = -1;
  evalmd:  // mutliplication + division
    if (eq[i] == '/' || eq[i] == '*') {
    int further = 0;
      if (eq[next] == '*' || eq[next] == '/') {
        do {
          further = find_next_symbol(next + 2, eq);
          if (further == -1) {
            break;
          }
        }
        while (eq[further] == '*' || // This searchs symbols after the next symbol
               eq[further] == '/');  // it is two because we dont want to search the number
                                                            // after the symbol: 3*2*42/2 -> after the second '*' 
                                                            // there has to be a number (42)
        // now we have + or - after / and *
        // so we can calculate whole result from left to right till that index (further)
        // 3*5-2/2*5-3*4/2
        if (further == -1) {
          further = len;
        }
//        for (int k = i; k < further; k++) {
//          printf("%c",eq[k]);
//        }
        printf("\n");
        char buffer[100] = { 0 };
        for (int k = last_symb + 1; k < further; k++) {
          buffer[k] = eq[k];
        }
        printf("\nbuffer: %s\n", buffer);
      } else {
        if (next != -1) {
          for (int j = last_symb + 1; j < next; j++) {
            buff[j - last_symb - 1] = eq[j];
            printf("%c", eq[j]);  //
          }
        } else {
          for (int j = last_symb + 1; j < len; j++) {
            buff[j - last_symb - 1] = eq[j];
            printf("%c", eq[j]);  //
          }
        }
        last_symb = i;
      }
    }
    // 3*5-2/2+1-3
    //		evalas://addition + substraction
    if (eq[i] == '+' || eq[i] == '-') {
      //				if(next != -1){
      //					for(int
      // j=last_symb+1;j<next;j++){
      // printf("%c", eq[j]);//
      //					}
      //				} else {
      //					for(int
      // j=last_symb+1;j<len;j++){
      // printf("%c", eq[j]);//
      //					}
      //				}
      last_symb = i;
    }
  }
  return 0;
}
int find_former_symbol(int start, char* eq) {
  int len = strlen(eq);
  assert(start <= len); // start cannot be greater than len
  for (int i = start; i > 0; i--) {
    for (int j = 0; j < list_len; j++) {
      if (eq[i] == list[j]) {
        return i;
      }
    }
  }
  return -1;  // not found
}


int find_next_symbol(int start, char* eq) {
  int len = strlen(eq);
  for (int i = start; i < len; i++) {
    for (int j = 0; j < list_len; j++) {
      if (eq[i] == list[j]) {
        return i;
      }
    }
  }
  return -1;  // not found
}

double single(char* ex) {  // this represents a single expression. like 3*7 but
                           // it could be anything!
  char left[100] = {0}, right[100] = {0};
  char exp;
  int len = strlen(ex);
  for (int i = len; i > 0; i--) {
    for (int j = 0; j < sizeof(symb_list) / sizeof(char); j++) {
      if (ex[i] == symb_list[j]) {
        for (int k = 0; k < i; k++) {
          left[k] = ex[k];
          //					switch(symb_list[j]){
          //						case '+':
          //					}
        }
        for (int k = i + 1; k < len; k++) {
          right[k - i - 1] = ex[k];
        }
        exp = ex[i];
        goto casting;
      }
    }
  }
casting:
  int nleft = atoi(left);
  int nright = atoi(right);
  int result = 0;
  switch (exp) {
    case '+':
      result = nleft + nright;
      break;
    case '-':
      result = nleft - nright;
      break;
    case '*':
      result = nleft * nright;
      break;
    case '/':
      result = nleft / nright;
      break;
      //			case '+':
      //				result = nleft+nright;
      //				break;
    default:
      perror("ERROR-01: Invalid expression! ");
      abort();
      break;
  }
  return result;
}

void get_input(char* buff) {
  int len = strlen(buff);
  // fgets(buff,len,stdin);
  scanf("%s", buff);
  buff[strcspn(buff, "\n")] = '\0';
}

void print(char* buff, int start, int end) {
  for (int i = start; i < end; i++) {
    printf("%c", buff[i]);
  }
  printf("\n");
}

void copy(char* from, int start, int end, char* to) {
  for (int i = start; i < end; i++) {
    to[i - start] = from[i];
  }
}

// inefficient
void clear_copy(char* from, int start_from, int end_from, int start_to, int end_to, char* to) { 
  /*assert((end_from - start_from) <= (end_to - start_to));*/

  for (int i = 0; i < end_to - start_to; i++) {
    to[start_to + i] = ' ';
  }
  for (int i = 0; i < end_from - start_from; i++) {
    to[start_to + i] = from[start_from + i];
  }
}
// int diff = start_from - start_to;
//  for (int i = 0; i < diff; i++) { // basically this means length
//    to[start_to + i] = from[start_from + i];
//  }
//  diff = abs( ( start_from - end_from ) - ( start_to - end_to ) ) + diff ; // adding length
//  for (int i = 0; i < diff; i++) {
//    to[start_to + i] = ' ';
//  }

bool has_any(char symbols[], char* list) {
  int len = strlen(list);
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < sizeof(*symbols) / sizeof(char); j++) {
      if (list[i] == symbols[j]) {
        return true;
      }
    }
  }
  return false;
}

// karuso
// boh rap
// halelua
// still lovin yu
// traveller
// shine on you crazy diamond
// show must go on
