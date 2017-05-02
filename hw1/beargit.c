#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/stat.h>

#include "beargit.h"
#include "util.h"

typedef unsigned long long int ULLONG;
/* Implementation Notes:
 *
 * - Functions return 0 if successful, 1 if there is an error.
 * - All error conditions in the function description need to be implemented
 *   and written to stderr. We catch some additional errors for you in main.c.
 * - Output to stdout needs to be exactly as specified in the function description.
 * - Only edit this file (beargit.c)
 * - You are given the following helper functions:
 *   * fs_mkdir(dirname): create directory <dirname>
 *   * fs_rm(filename): delete file <filename>
 *   * fs_mv(src,dst): move file <src> to <dst>, overwriting <dst> if it exists
 *   * fs_cp(src,dst): copy file <src> to <dst>, overwriting <dst> if it exists
 *   * write_string_to_file(filename,str): write <str> to filename (overwriting contents)
 *   * read_string_from_file(filename,str,size): read a string of at most <size> (incl.
 *     NULL character) from file <filename> and store it into <str>. Note that <str>
 *     needs to be large enough to hold that string.
 *  - You NEED to test your code. The autograder we provide does not contain the
 *    full set of tests that we will run on your code. See "Step 5" in the homework spec.
 */

/* beargit init
 *
 * - Create .beargit directory
 * - Create empty .beargit/.index file
 * - Create .beargit/.prev file containing 0..0 commit id
 *
 * Output (to stdout):
 * - None if successful
 */

int beargit_init(void) {
  fs_mkdir(".beargit");

  FILE* findex = fopen(".beargit/.index", "w");
  fclose(findex);
  
  write_string_to_file(".beargit/.prev", "0000000000000000000000000000000000000000");

  return 0;
}


/* beargit add <filename>
 * 
 * - Append filename to list in .beargit/.index if it isn't in there yet
 *
 * Possible errors (to stderr):
 * >> ERROR: File <filename> already added
 *
 * Output (to stdout):
 * - None if successful
 */

int beargit_add(const char* filename) {
  FILE* findex = fopen(".beargit/.index", "r");
  FILE *fnewindex = fopen(".beargit/.newindex", "w");

  char line[FILENAME_SIZE];
  while(fgets(line, sizeof(line), findex)) {
    strtok(line, "\n");
    if (strcmp(line, filename) == 0) {
      fprintf(stderr, "ERROR: File %s already added\n", filename);
      fclose(findex);
      fclose(fnewindex);
      fs_rm(".beargit/.newindex");
      return 3;
    }

    fprintf(fnewindex, "%s\n", line);
  }

  fprintf(fnewindex, "%s\n", filename);
  fclose(findex);
  fclose(fnewindex);

  fs_mv(".beargit/.newindex", ".beargit/.index");

  return 0;
}


/* beargit rm <filename>
 * 
 * Remove the file filename from .beargit/.index
 * @param filename, the file to remove from beargit tracking
 * @return 0 if successful, or 1 if filename is not being tracked
 *
 */

int beargit_rm(const char* filename) {
    FILE* findex = fopen(".beargit/.index", "r");
    FILE *fnewindex = fopen(".beargit/.newindex", "w");
    int found = 0;

    char line[FILENAME_SIZE];
    while(fgets(line, sizeof(line), findex)) {
        strtok(line, "\n");
        if (strcmp(line, filename) == 0) 
            found++;
        else 
            fprintf(fnewindex, "%s\n", line);
    }
    if (!found) {
        fprintf(stderr, "ERROR: File %s not tracked\n", filename);
        fclose(findex);
        fclose(fnewindex);
        fs_rm(".beargit/.newindex");
        return 1;
    }

    fclose(findex);
    fclose(fnewindex);

    fs_mv(".beargit/.newindex", ".beargit/.index");
    return 0;
}

/* beargit commit -m <msg>
 *
 * See "Step 3" in the homework 1 spec.
 *
 */

const char* go_bears = "GO BEARS!";

int is_commit_msg_ok(const char* msg) {
    int i = 0, j = 0; 
    while(*msg != '\0') {

        // find 'G'
        while (msg[i] != go_bears[j] && msg[i] != '\0')
            i++;
        
        // have we reached the end of the msg? 
        if (msg[i] == '\0')
            break; 

        // Check for "GO BEARS!"
        while(msg[i] == go_bears[j++] && go_bears[j] != '\0')
            i++;
        if (go_bears[j] == '\0' && go_bears[j-1] == msg[i])
            return 1;
    }
    return 0;
}

/* Return the base to the power of exponent.
 * requires base > 0 && exponent >= 0 */
ULLONG power(int base, int exponent) {
    ULLONG result = (ULLONG) 1;
    ULLONG b = (ULLONG) base;
    for ( ; exponent > 0; exponent--)
        result *= b;
    return result;
}

ULLONG base3_to_long(char* id) {
    ULLONG result = 0;
    int e;
    char *start = id;
    // get to end of array
    while(*id != '\0')
        id++;
    for(--id, e = 0; start <= id; e++, id--) {
        if (*id == 'c') // c == 2
            result += 2l * power(3, e);
        if (*id == '6') // 6 == 1
            result += power(3, e);
        // 1 == 0, so continue
    }
    return result;
}

void long_to_base3(char* str, ULLONG n, int len) {
    ULLONG remainder = n, quotient; 
    char result[len--];
    result[0] = '\0'; // ensure empty string
    while (len >= 0) {
        if ((quotient = remainder / power(3, len))) {
            if(len) 
                remainder %= power(3, len);
            if (quotient == 2)
                strcat(result, "c");
            if (quotient == 1)
                strcat(result, "6");
        }
        else {
            strcat(result, "1");
        }
        len--;
    }
    strcpy(str, result);
}

void next_commit_id(char* commit_id) {
    // if first commit
    if (strcmp(commit_id, "0000000000000000000000000000000000000000") == 0) {
        strcpy(commit_id, "1111111111111111111111111111111111111111");
    }
    else {
        ULLONG id_number = base3_to_long(commit_id);
        id_number++;
        long_to_base3(commit_id, id_number, strlen(commit_id));
    }
}

int beargit_commit(const char* msg) {
  if (!is_commit_msg_ok(msg)) {
    fprintf(stderr, "ERROR: Message must contain \"%s\"\n", go_bears);
    return 1;
  }

  char commit_id[COMMIT_ID_SIZE];
  read_string_from_file(".beargit/.prev", commit_id, COMMIT_ID_SIZE);
  next_commit_id(commit_id);

  /* COMPLETE THE REST */

  return 0;
}

/* beargit status
 *
 * Read the file .beargit/.index and print a line for each tracked file.
 * Formatted like this (where <file*> is the filename):
 *
 *   Tracked files:
 *
 *     <file1>
 *     [...]
 *     <fileN>
 *
 *   <N> files total
 *
 * @return 0
 */

int beargit_status() {
    int count = 0;
    FILE* findex = fopen(".beargit/.index", "r");
    char line[FILENAME_SIZE];

    printf("Tracked files:\n\n");
    while(fgets(line, sizeof(line), findex)) {
        strtok(line, "\n");
        printf("\t%s\n", line);
        count++;
    }
    fclose(findex);
    printf("\n%d files total\n", count);

    return 0;
}

/* beargit log
 *
 * See "Step 4" in the homework 1 spec.
 *
 */

int beargit_log() {

    return 0;
}
