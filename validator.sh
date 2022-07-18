# alias kcc='gcc -Wall -Wextra -Werror'
kcc $LDFLAGS $CPPFLAGS corsair.c -lssl -lcrypto && ./a.out && rm -rf a.out
kcc $LDFLAGS $CPPFLAGS -o certpubkey certpubkey.c -lssl -lcrypto && ./certpubkey && rm -rf certpubkey

### INSTALL OPENSSL MAC ###
brew install openssl
brew link --force openssl
export LDFLAGS="-L/System/Volumes/Data/sgoinfre/goinfre/Perso/jseijo-p/homebrew/opt/openssl@3/lib"
export CPPFLAGS="-I/System/Volumes/Data/sgoinfre/goinfre/Perso/jseijo-p/homebrew/opt/openssl@3/include"

export LDFLAGS="-L/System/Volumes/Data/sgoinfre/goinfre/Perso/jseijo-p/homebrew/opt/openssl@1.1/lib"
export CPPFLAGS="-I/System/Volumes/Data/sgoinfre/goinfre/Perso/jseijo-p/homebrew/opt/openssl@1.1/include"

# ln -s /usr/local/opt/openssl/include/openssl /usr/local/include
# ln -s /usr/local/Cellar/openssl/[version]/include/openssl /usr/bin/openssl

gcc $LDFLAGS $CPPFLAGS -ggdb -Wall -Wextra -o rsa_test rsa_test.c -lcrypto
gcc $LDFLAGS $CPPFLAGS -o certpubkey certpubkey.c -lssl -lcrypto && ./certpubkey
gcc $LDFLAGS3 $CPPFLAGS3 -o certpubkey certpubkey.c -lssl -lcrypto

# Generar certificados usando OpenSSL
openssl req -x509 -newkey rsa:4096 -sha256 -days 3650 -nodes \
  -keyout example.key -out example.crt -subj "/CN=example.com"
