### Functionality

1. **Input Validation**
   - The program requires exactly one command-line argument. If the number of arguments is incorrect, it exits with a return code `1`.

2. **String Duplication**
   - The input string (`argv[1]`) is duplicated using `ft_strdup` for safe manipulation.

3. **Tokenization**
   - The string is parsed into tokens using `parse_string(str)`.
   - The result is a linked list of tokens stored in `list`.

4. **Syntax Validation**
   - The `parser_check(list)` function checks the token list for syntax errors.
   - If an error is detected, `token_identify_error(err)` is called to identify and report the specific error, and the program exits with the error code.

5. **Token Processing**
   - **Printing Initial Tokens**: The token list is printed using `print_token_list(list)` before any modifications.
   - **Token Identification**: The `parser_identify(list)` function further classifies or adjusts the tokens based on specific rules. The updated list is printed.
   - **Defining Priorities**: The `parser_define_priority(&list)` function assigns priorities to tokens in the list. The list is printed after this step.
   - **Joining Tokens**: The `parser_join_tokens(list)` function combines or modifies tokens based on defined logic. The final version of the list is printed.

6. **Cleanup**
   - The token list is freed using `free_token(list)`, which releases memory for the tokens and their content.
   - The duplicated string (`str`) is also freed.

---

### Execution Stages
- **Before any processing**: The original token list is printed.
- **After identification**: The tokens are classified or adjusted.
- **After priority assignment**: The priority for each token is defined.
- **After joining tokens**: The final transformed token list is displayed.

This sequence provides a clear view of the token list's evolution throughout the program's execution.
