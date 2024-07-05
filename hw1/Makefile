target=x86_64-apple-darwin

.PHONY: all clean
all: color echo143 hex2rgb oct2perm perm2oct rgb2hex

clean:
	rm -rf  color echo143 hex2rgb oct2perm perm2oct rgb2hex

%: %.c
	clang -Wall -Wextra -pedantic -std=c11 -O2 -target $(target) -o $@ $^
