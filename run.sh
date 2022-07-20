#!/usr/bin/env bash

echo "Begining compilation..."
gcc -Wall -Wextra -Werror $LDFLAGS $CPPFLAGS corsair.c -lssl -lcrypto -o corsair
echo "Success compilation!"
echo ""
echo "Usage"
echo "./corsair -incert example.crt"
echo "./corsair -p1 308686191349562099250656893787 -p2 849807305654028828946669531693"

# kcc  $LDFLAGS $CPPFLAGS corsair.c -lssl -lcrypto -o corsair && ./corsair -incert example.crt && rm -rf corsair

# # alias kcc='gcc -Wall -Wextra -Werror'
# kcc $LDFLAGS $CPPFLAGS corsair.c -lssl -lcrypto && ./a.out -p1 308686191349562099250656893787 -p2 849807305654028828946669531693 && rm -rf a.out
# kcc $LDFLAGS $CPPFLAGS corsair.c -lssl -lcrypto && ./a.out -p1 956443055318309275125107150089415737684178159988563615880215075094885702341633561752314081541338805338884255141137612733464008695580931948157407231491373856657373934896642310561185637058211462030092505824642665689935086500639275811730760067142790250723139006024700283651774141431774326687352226661139 -p2 894791388356254901393041463485994792478838009940419523036888346436161503066281261828167684530420388763112556439302434503072445311932496021410603578352388942294923136092977319877618737648682745313478108489460538046488547723726538928873870384584576214916127832352093452714584258045857940481926366744231 && rm -rf a.out
# kcc $LDFLAGS $CPPFLAGS -o certpubkey certpubkey.c -lssl -lcrypto && ./certpubkey && rm -rf certpubkey
#
# ### INSTALL OPENSSL MAC ###
# brew install openssl
# export LDFLAGS="-L/System/Volumes/Data/sgoinfre/goinfre/Perso/jseijo-p/homebrew/opt/openssl@3/lib"
# export CPPFLAGS="-I/System/Volumes/Data/sgoinfre/goinfre/Perso/jseijo-p/homebrew/opt/openssl@3/include"
# export LDFLAGS="-L/System/Volumes/Data/sgoinfre/goinfre/Perso/jseijo-p/homebrew/opt/openssl@1.1/lib"
# export CPPFLAGS="-I/System/Volumes/Data/sgoinfre/goinfre/Perso/jseijo-p/homebrew/opt/openssl@1.1/include"
#
# # Generar certificados usando OpenSSL
# openssl req -x509 -newkey rsa:4096 -sha256 -days 3650 -nodes \
#   -keyout example.key -out example.crt -subj "/CN=example.com"
#
# # https://bigprimes.org
