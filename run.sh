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

# pub key
# MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCqGKukO1De7zhZj6+H0qtjTkVxwTCpvKe4eCZ0FPqri0cb2JZfXJ/DgYSF6vUpwmJG8wVQZKjeGcjDOL5UlsuusFncCzWBQ7RKNUSesmQRMSGkVb1/3j+skZ6UtW+5u09lHNsj6tQ51s1SPrCBkedbNf0Tp0GbMJDyR4e9T04ZZwIDAQAB
# Hex modulus
# 00AA18ABA43B50DEEF38598FAF87D2AB634E4571C130A9BCA7B878267414FAAB8B471BD8965F5C9FC3818485EAF529C26246F3055064A8DE19C8C338BE5496CBAEB059DC0B358143B44A35449EB264113121A455BD7FDE3FAC919E94B56FB9BB4F651CDB23EAD439D6CD523EB08191E75B35FD13A7419B3090F24787BD4F4E1967
# Decimal modulus
# 119445732379544598056145200053932732877863846799652384989588303737527328743970559883211146487286317168142202446955508902936035124709397221178664495721428029984726868375359168203283442617134197706515425366188396513684446494070223079865755643116690165578452542158755074958452695530623055205290232290667934914919

openssl rsa -in res_public.pem -noout &> /dev/null
if [ $? != 0 ] ; then
    echo "NOT a RSA public key in PEM format 1"
fi

openssl pkey -in res_public.pem -noout &> /dev/null
if [ $? != 0 ] ; then
    echo "NOT a public key in PEM format 1"
fi
openssl rsa -in res_private.pem -noout &> /dev/null
if [ $? != 0 ] ; then
    echo "NOT a RSA private key in PEM format 2"
fi

openssl pkey -in res_private.pem -noout &> /dev/null
if [ $? != 0 ] ; then
    echo "NOT a private key in PEM format 2"
fi
