#ifndef PARSE_TEMPFILE_H
# define PARSE_TEMPFILE_H

# include <sys/types.h>

# define BUF_SIZE      256
# define BASE          "/tmp/heredoc_"
# define RANDOM_BYTES  8
# define MAX_TRY       100

typedef struct s_tempfile
{
	char         *filename;
	unsigned char rnd[RANDOM_BYTES];
	char         hexpart[RANDOM_BYTES * 2 + 1];
	int          tries;
	int          fd;
}   t_tempfile;

char *generate_temp_filename(void);

#endif
