For geany:

```
g++ -pedantic -fsanitize=address -Wall -Wextra -O2 -Wshadow -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -Wall -c "%f"
```
```
g++ -pedantic -fsanitize=address -Wall -Wextra -O2 -Wshadow -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -Wall -o "%e" "%f"
```