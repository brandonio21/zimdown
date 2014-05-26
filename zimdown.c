/******************************************************************************
* File:    zimdown.c
* Author:  Brandon Milton
* Website: http://brandonsoft.com
* GitHub:  http://github.com/brandonio21
* May 19, 2014
*
* The purpose of zimdown.c is to provide an easy way to convert ZIM files into
* markdown files. Basically, this program simply converts the syntax of each
* markup format so that they can be interchanged.
******************************************************************************/
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "strings.h"
#include "symbols.h"

#define FILEOPEN_READ "r"
#define FILEOPEN_WRITE "w"
#define EXIT_FAILURE 0
#define EXIT_SUCCESS 1


void convertLine(char *line, char *result);
void convertHeader(char *toConvert, char *result);
void convertItalics(char *toConvert, int *result);
void convertBold(char *toConvert);


int main(int argc, const char* argv[])
{
  /* The first thing we need to do is check the parameters */
  /* If the user specified no options */
  if (argc <= 1)
  {
    printf("%s", STR_USAGE);
    return EXIT_FAILURE;
  }
    
  /* Now, if the user specified the name of a file, do something */
  /* for now, we will just assume that they specified a correct filepath */
  FILE *readFile = fopen(argv[1], FILEOPEN_READ);
  FILE *writeFile = fopen(argv[2], FILEOPEN_WRITE);
  if (readFile == NULL) 
  {
    perror(STR_ERR_READFILE); 
    return EXIT_FAILURE;
  }
  if (writeFile == NULL)
  {
    perror(STR_ERR_WRITEFILE);
    return EXIT_FAILURE;
  }

  /* Now we are going to read every line of the first file */
  char readFileLine[BUFSIZ];
  while (fgets(readFileLine, BUFSIZ, readFile) != NULL)
  {
    /* While there are still lines to read from the file, we analyze the line */
    printf("Read Line: %s", readFileLine);
    char lineToWrite[BUFSIZ];
    int i = 0;
    convertLine(readFileLine, lineToWrite);
    printf("Converted Line: %s", lineToWrite);
    fwrite(lineToWrite, sizeof(char), strlen(lineToWrite), writeFile);
  }

  /* Now close the files */
  fclose(readFile);
  fclose(writeFile);
}

void convertLine(char *line, char *result)
{
  printf("Line to Convert: %s", line);
  int index = 0;
  int header = 1;
  int changes = 0;
  while (line[index] != '\0')
  {
    int resultant = 0;
    switch (line[index])
    {
      case ZIM_HEADER :
        if (header == 1)
        {
          convertHeader(line, result);
          if (strcmp(line, result) == 0)
          {
            header = 0;
            changes = 1;
            break;
          }
          else
            return;
        }


      case ZIM_ITALICS :
        convertItalics(line, &resultant);
        strcpy(result, line);
        if (resultant == 1)
          index-=3; /* makeup for lost characters */
        changes = 1;
        break;
    }
    ++index;
  }
  if (changes == 0)
    strcpy(result, line);
} 

void convertItalics(char *toConvert, int *result)
{
  /* look for the first pair of slashes */
  char *slash = strchr(toConvert, ZIM_ITALICS);
  while (*(slash + 1) != ZIM_ITALICS && slash != NULL)
    slash = strchr(toConvert, ZIM_ITALICS);

  /* now that the first pair of slashes has been found, string at slash+2 */
  char *secondSlash = strchr(slash+2, ZIM_ITALICS);
  while (secondSlash != NULL && *(secondSlash + 1) != ZIM_ITALICS)
    secondSlash = strchr(slash+2, ZIM_ITALICS);

  /* replace the characters */
  *slash = '\0';
  *(slash+1) = MARKDOWN_ITALICS;
  *secondSlash = '\0';
  *(secondSlash+1) = MARKDOWN_ITALICS;

  *result = 1;

  /* Now let's cleverly recombine the strings */
  strcat(toConvert, slash+1);
  strcat(toConvert, secondSlash+1);

}

void convertBold(char *toConvert)
{
  /* look for the first pair of asterisks */
  char *star = strchr(toConvert, ZIM_BOLD);
  while (star != NULL && *(star + 1) != ZIM_BOLD)
    star = strchr(toConvert, ZIM_BOLD);

  /* Now we need to find the second pair of asterisks */
  char *secondStar = strchr(star+2, ZIM_BOLD);
  while (secondStar != NULL && *(secondStar + 1) != ZIM_BOLD)
    secondStar = strchr(star+2, ZIM_BOLD);

  /* replace the characters */
  *star = MARKDOWN_BOLD;
  *(star+1) = MARKDOWN_BOLD;
  *secondStar = MARKDOWN_BOLD;
  *(secondStar+1) = MARKDOWN_BOLD;

}

void convertHeader(char *toConvert, char *result)
{
  /* First, we need to find the index of the first space */
  char *space = strchr(toConvert, ' ');

  /* Now replace the first space with a null terminator */
  *space = '\0';
  space++; /* increase the space pointer */


  /* Now let's find the index of the end of the message */
  char *secondSpace = strchr(space, ZIM_HEADER);

  /* Now replace the end of the message space with a null terminator */
  *(secondSpace - 1) = '\0';

  /* Now we need to see if the lengths of the headers are equal */
  int secondCount = 1;
  while (*(secondSpace + secondCount) == ZIM_HEADER)
    secondCount++;

  if ((space-1-toConvert) != secondCount)
  {
    /* the second header block isn't completing the header, it's not one! */
    /* revert the string */
    *(space-1) = ' ';
    *(secondSpace-1) = ' ';
    strcpy(result, toConvert);
    return;
  }


  /* Now that we have our header string and text, convert them to markdown */
  /* First, get the header length thing */
  int length = ZIM_MD_HEADER_DIFF - (space - toConvert);

  /* Now we need to put that many markdown headers in front */
  int i = 0;
  for (i = 0; i < length; i++)
    result[i] = MARKDOWN_HEADER;
  /* Insert a space and then insert the message */
  result[i] = ' ';
  strcat(result, space);
}
