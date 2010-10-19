if [ $1 = null ] 
then
	./Partikkel.out $* > /dev/null
elif [ $1 ]
then
	./Partikkel.out $*
else
	./Partikkel.out 
fi

#./Partikkel.out > /dev/pts/3; echo FERDIG > /dev/pts/3

#Evt /dev/pts/3
