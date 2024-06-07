#ifndef IPV4NETID
#define IPV4NETID

int init_regex(regex_t *regex);
char **splitup(char *string);
int *to_decimal(char **input);
int **to_binary(int *input);
int binary_to_decimal(int *input);
int **get_netid(int **ip, int **subnet);
void print_binary_address(int **binary);
char *get_valid_input(char *prompt_text, regex_t *regex);
int is_within_8bit_range(int *ip);
int check_range(char *string);
void print_result_table(int **ip, int **subnet, int **netid);

#endif
