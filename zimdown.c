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
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "strings.h"
#include "symbols.h"

#define FILEOPEN_READ "r"
#define FILEOPEN_WRITE "w"


void convertLine(char *line, char *result);
void convertHeader(char *toConvert, char *result);
void convertItalics(char *toConvert, int *result);
void convertBold(char *toConvert, int *result);
void convertImage(char *toConvert, char *result);


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
    for (i = 0; i < BUFSIZ; i++)
      lineToWrite[i] = '\0';
    convertLine(readFileLine, lineToWrite);

    /* Now we need to remove the newline, and add two spaces before it */
    char *newline;
    if ((newline = strchr(lineToWrite, '\n')) != NULL)
    {
      *newline = ' ';
      strcat(lineToWrite, " \n");
    }
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
  int image = 1;
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

      case ZIM_IMAGE_OPEN :
        if (image == 1)
        {
          printf("%s\n", "converting img");
          convertImage(line, result);
          printf("%s\n", "done converting img");
          if (strcmp(line, result) == 0)
          {
            image = 0;
            changes = 1;
            break;
          }
          else
            return;
        }


      case ZIM_BOLD :
        convertBold(line, &resultant);
        strcpy(result, line);
        changes = 1;
        break;

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
  while (slash != NULL && *(slash + 1) != ZIM_ITALICS)
    slash = strchr(slash+1, ZIM_ITALICS);

  if (slash == NULL)
  {
    *result = 0;
    return;
  }


  /* now that the first pair of slashes has been found, string at slash+2 */
  char *secondSlash = strchr(slash+2, ZIM_ITALICS);
  while (secondSlash != NULL && *(secondSlash + 1) != ZIM_ITALICS)
    secondSlash = strchr(secondSlash+1, ZIM_ITALICS);

  if (secondSlash == NULL)
  {
    *result = 0;
    return;
  }

  /* replace the characters */
  *slash = MARKDOWN_ITALICS;
  *(slash+1) = MARKDOWN_ITALICS;
  *secondSlash = MARKDOWN_ITALICS;
  *(secondSlash+1) = MARKDOWN_ITALICS;

  /* Now we need to shift the whitespace out */
  char *whitespace;   
  int whitespaceCount = 0;

  /* let's count how many spaces there are */
  while (*(whitespace = (slash+2+whitespaceCount)) == ' ' || *whitespace == '\t')
    ++whitespaceCount;

  /* now let's swap it all out */
  char *ps = whitespace-1;
  while (whitespaceCount > 0)
  {
    char temp = *(ps - whitespaceCount + 1); /* set temp to first whitespace */
    *(ps - whitespaceCount + 1) = *slash;    /* swap first space and white */
    *(slash) = temp;

    slash++;
    whitespaceCount--;
  }
  

  

  /* Let's count whitespace before italics things */
  whitespaceCount = 0;
  while (*(whitespace = secondSlash-1-whitespaceCount) == ' ' || 
           *whitespace == '\t')
    ++whitespaceCount;

  /* now let's shift it all out */
  ps = whitespace+1;
  while (whitespaceCount > 0)
  {
    char temp = *(ps + whitespaceCount - 1);
    *(ps + whitespaceCount - 1) = *(secondSlash+1);
    *(secondSlash+1) = temp;

    secondSlash--;
    whitespaceCount--;
  }
  /* Now we need to move all other things left */
  int index = slash+2-toConvert;
  for(index = (slash+2-toConvert); index <= secondSlash-toConvert; index++)
    toConvert[index-1] = toConvert[index];

  /* Now let's move all the things after the slashes left */
  int secondIndex = secondSlash-toConvert+2;
  while (toConvert[secondIndex] != '\0')
  {
    toConvert[secondIndex-2] = toConvert[secondIndex];
    secondIndex++;
  }
  toConvert[secondIndex-2] = '\0'; /* end will null! */

  *result = 1; /* We did changes, tell the program */

  /* Now let's cleverly recombine the strings */
  printf("\nFinal  String: %s", toConvert);

}

void convertBold(char *toConvert, int *result)
{
  /* look for the first pair of asterisks */
  char *star = strchr(toConvert, ZIM_BOLD);
  while (star != NULL && *(star + 1) != ZIM_BOLD)
    star = strchr(star+1, ZIM_BOLD);

  if (star == NULL)
  {
    *result = 0;
    return;
  }

  /* Now we need to find the second pair of asterisks */
  char *secondStar = strchr(star+2, ZIM_BOLD);
  while (secondStar != NULL && *(secondStar + 1) != ZIM_BOLD)
    secondStar = strchr(star+3, ZIM_BOLD);

  if (secondStar == NULL)
  {
    *result = 0;
    return;
  }


  /* replace the characters */
  *star = MARKDOWN_BOLD;
  *(star+1) = MARKDOWN_BOLD;
  *secondStar = MARKDOWN_BOLD;
  *(secondStar+1) = MARKDOWN_BOLD;

  /* Markdown bolding must be **cccc** where c is a character. Remove spaces */
  char *space;
  int spaceCount = 0;

  /* Let's count how many spaces there are */
  while (*(space = (star+2+spaceCount)) == ' ' || *space == '\t')
    ++spaceCount;

  /* now we need to shift it all left */
  char *ps = space-1;
  while (spaceCount > 0)
  {
    char temp = *(ps - spaceCount + 1);
    *(ps - spaceCount + 1) = *star;
    *star = temp;

    star++;
    spaceCount--;
  }

  /* Now let's count how many spaces are to the left of second set */
  spaceCount = 0;
  while (*(space = (secondStar-1-spaceCount)) == ' ' || *space == '\t')
    ++spaceCount;

  /* Now let's shift it all left */
  ps = space+1;
  while (spaceCount > 0)
  {
    char temp = *(ps + spaceCount - 1);
    *(ps + spaceCount - 1) = *(secondStar+1);
    *(secondStar+1) = temp;

    secondStar--;
    spaceCount--;
  }
  

}

void convertImage(char *toConvert, char *result)
{
  printf("%s\n", "first process");
  /* First, we need to find the index of the first curly brace */
  char *brace = strchr(toConvert, ZIM_IMAGE_OPEN);
  while (brace != NULL && *(brace + 1) != ZIM_IMAGE_OPEN)
    brace = strchr(brace+1, ZIM_IMAGE_OPEN);

  if (brace == NULL)
  {
    strcpy(toConvert, result);
    return;
  }

  printf("%s\n", "second process");
  /* second, we need to find the index of the closing curly brace */
  char *closeBrace = strchr(toConvert, ZIM_IMAGE_CLOSE);
  while (closeBrace != NULL && *(closeBrace + 1) != ZIM_IMAGE_CLOSE)
    closeBrace = strchr(closeBrace+1, ZIM_IMAGE_CLOSE);

  if (closeBrace == NULL)
  {
    strcpy(toConvert, result);
    return;
  }

  printf("%s\n", "third process");
  /* Now let's switch the symbols */
  *(closeBrace) = '\0';
  *(brace+1) = MARKDOWN_IMAGE_OPEN;


  printf("%s\n", "combining");
  /* Now we need to combine everything */
  strcat(result, "![alt text]");
  strcat(result, brace+1);
  strcat(result, " \"Title Text\"");
  strcat(result, ")");
  printf("%s\n", "done");
}
void convertHeader(char *toConvert, char *result)
{
  /* First, we need to find the index of the first space */
  char *space = strchr(toConvert, ' ');

  if (space == NULL) /* There is no space! Not a header! Return! */
  {
    strcpy(result, toConvert);
    return;
  }


  /* Now replace the first space with a null terminator */
  *space = '\0';
  space++; /* increase the space pointer */


  /* Now let's find the index of the end of the message */
  char *secondSpace = strchr(space, ZIM_HEADER);

  if (secondSpace == NULL) /* Not a properly formatted header! */
  {
    /* convert string to what it was before processing and return */
    *(space-1) = ' ';
    strcpy(result, toConvert);
    return;
  }

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
  *(secondSpace - 1) = '\n';
  *secondSpace = '\0';
  strcat(result, space);
}
