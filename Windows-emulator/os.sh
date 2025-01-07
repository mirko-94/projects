#!/bin/bash

clear


computer()
{

echo "============================MyComputer==========================="
		
MYDIR=${mc}
cd $MYDIR


#first pipe cuts extension, next one enumerate
ls -1 $MYDIR | cut -f1 -d '.' | awk '{printf "%d. %s\n", NR, $0;}'  

if [ -z "$(ls -A ${mc})" ]; then
   	echo ""
	echo "1.Create file"
	echo "4.Exit"
else
	echo ""
	echo "1.Create file"
	echo "2.Delete file"
	echo "3.Edit file"
	echo "4.Exit"
fi


echo ""
echo "Enter selection [1-4] > "
read INPUT

case $INPUT in
	1)      
		echo "File name:"
		read new 
		
		help=$(mktemp /${mc}/${new}.txt.XXX)
		mcFiles+=(${help})

		computer
		;;
	
	2)	
		echo "File name:"
		read del

				


		for i in "${mcFiles[@]}"
		do
		
     		if [[ "$i" == *"$del"* ]]; then
     		rbFiles+=(${del}.txt)	
     		cp "$i" /${rb}/${del}.txt 	
     		rm "$i"
     		
     		fi
		done
		
		computer
		;;
		
	3)      
		echo "File name:"
		read ed
		
		for i in "${mcFiles[@]}"
		do
		
     		if [[ "$i" == *"$ed"* ]]; then
     		
     		sudo nano ${i}
     		
     		fi
		done
		
		computer
		;;		
		
	4)
		get_in_home_screen
		;;
		

  esac
}



music()
{

echo "=============================MyMusic============================="
		
MYDIR=${mm}
cd $MYDIR

ls -1 $MYDIR | cut -f1 -d '.' | awk '{printf "%d. %s\n", NR, $0;}'      	      

if [ -z "$(ls -A ${mm})" ]; then
   	echo ""
	echo "1.Create file"
	echo "4.Exit"
else
	echo ""
	echo "1.Create file"
	echo "2.Delete file"
	echo "3.Edit file"
	echo "4.Exit"
fi


echo ""
echo "Enter selection [0-4] > "
read INPUT

case $INPUT in
	1)      
		echo "File name:"
		read new 
		
		help=$(mktemp /${mm}/${new}.txt.XXX)
		mmFiles+=(${help})

		music
		;;
	
	2)	
		echo "File name:"
		read del
	
		
		for i in "${mmFiles[@]}"
		do
		
     		if [[ "$i" == *"$del"* ]]; then
     		cp "$i" /${rb}/${del}.txt
     		rm "$i"
     		
     		fi
		done
		
		music
		;;	
	
	3)	echo "File name:"
		read ed
		
		for i in "${mmFiles[@]}"
		do
		
     		if [[ "$i" == *"$ed"* ]]; then
     		
     		sudo nano ${i}
     		
     		fi
		done
		
		music
		;;
	
		
	4)
		get_in_home_screen
		;;
	
  esac
}








pictures()
{

echo "============================MyPictures==========================="
		
MYDIR=${mp}
cd $MYDIR

ls -1 $MYDIR | cut -f1 -d '.' | awk '{printf "%d. %s\n", NR, $0;}'      	      

if [ -z "$(ls -A ${mp})" ]; then
   	echo ""
	echo "1.Create file"
	echo "4.Exit"
else
	echo ""
	echo "1.Create file"
	echo "2.Delete file"
	echo "3.Edit file"
	echo "4.Exit"
fi


echo ""
echo "Enter selection [0-4] > "
read INPUT

case $INPUT in
	1)      
		echo "File name:"
		read new 
		
		help=$(mktemp /${mp}/${new}.txt.XXX)
		mpFiles+=(${help})

		pictures
		;;
	
	2)	
		echo "File name:"
		read del

		
		for i in "${mpFiles[@]}"
		do
		
     		if [[ "$i" == *"$del"* ]]; then
     		cp "$i" /${rb}/${del}.txt
     		rm "$i"
     		
     		fi
		done
		
		pictures
		;;	
	
	3)	echo "File name:"
		read ed
		
		for i in "${mpFiles[@]}"
		do
		
     		if [[ "$i" == *"$ed"* ]]; then
     		
     		sudo nano ${i}
     		
     		fi
		
		done
		
		pictures
		;;
	
	
		
	4)
		get_in_home_screen
		;;
	
  esac
}

bin()
{

echo "===========================RecycleBin============================"
		
MYDIR=${rb}
cd $MYDIR

 #first pipe cuts extension, next one enumerate
ls -1 $MYDIR | cut -f1 -d '.' | awk '{printf "%d. %s\n", NR, $0;}'  


if [ -z "$(ls -A ${rb})" ]; then
   	echo ""
	echo "1.Create file"
	echo "4.Exit"
else
	echo ""
	echo "1.Create file"
	echo "2.Delete file"
	echo "3.Empty the recycle bin"
	echo "4.Exit"
fi


echo ""
echo "Enter selection [0-4] > "
read INPUT

case $INPUT in
	1)      
		echo "File name:"
		read new 
		
		help=$(mktemp /${rb}/${new}.txt.XXX)
		rbFiles+=(${help})

		bin
		;;
	
	2)	
		echo "File name:"
		read del
		
		for i in "${rbFiles[@]}"
		do
		
     		if [[ "$i" == *"$del"* ]]; then
     		rm "$i"
     		fi
		done
		
		bin
		;;	
	
	3)	
		for i in "${rbFiles[@]}"
		do
	
     		rm "$i"
		unset rbFiles
		
		done
		
		bin
		;;
	
	
		
	4)
		get_in_home_screen
		;;
	
  esac
}


user()
{

echo "==============================User==============================="
		
MYDIR=${us}
cd $MYDIR

ls -1 $MYDIR | cut -f1 -d '.' | awk '{printf "%d. %s\n", NR, $0;}'      	      

if [ -z "$(ls -A ${us})" ]; then
   	echo ""
	echo "1.Create file"
	echo "4.Exit"
else
	echo ""
	echo "1.Create file"
	echo "2.Delete file"
	echo "3.Edit file"
	echo "4.Exit"
fi




echo ""
echo "Enter selection [0-4] > "
read INPUT

case $INPUT in
	1)      
		echo "File name:"
		read new 
		
		help=$(mktemp /${us}/${new}.txt.XXX)
		usFiles+=(${help})

		user
		;;
	
	2)	
		echo "File name:"
		read del	
		
		for i in "${usFiles[@]}"
		do
		
     		if [[ "$i" == *"$del"* ]]; then
     		cp "$i" /${rb}/${del}.txt	
     		rm "$i"
     		fi
		done
		user
		;;	
	
	3)	echo "File name:"
		read ed
		
		for i in "${usFiles[@]}"
		do
		
     		if [[ "$i" == *"$ed"* ]]; then
     		sudo nano ${i}
     		fi
		done
		
		user
		;;
	
		
	4)
		get_in_home_screen
		;;
	
  esac
}

sett()
{

echo "============================Settings============================="
		
MYDIR=${mc}
cd $MYDIR
     	      

echo ""
echo "1.Disk Usage"
echo "2.System Information"
echo "4.Exit"


echo ""
echo "Enter selection [0-4] > "
read INPUT

case $INPUT in
	1)  
        echo "================================================================="
	    echo "Local Disk(C:):"
	    echo "================================================================="
	    for i in "${osFiles[@]}"
	     do 
         	#echo "${i:0:-4}"  
		 	#stat --printf="%s bytes" ${i}
		 	du -sh ${i} 
		done 
		sett
		;;
	
	2)	
		lscpu
		sett
		;;	
	
		
	4)
		get_in_home_screen
		;;
	
  esac
}




get_in_home_screen()
{
echo ""
echo ""
echo "===========================Home Screen==========================="
echo "1.MyComputer"
echo "2.MyMusic"
echo "3.MyPictures"
echo "4.RecycleBin"
echo "5.User"
echo "6.Settings"
echo "7.Exit"
echo ""
echo "Enter selection [1-7] > "
read INPUT

case $INPUT in
	1)
		computer
		;;
	2)
		music
		;;
	3)
		pictures
		;;
		
	4)
		bin
		;;
		
	5)
		user
		;;

	6)
		sett
		;;		
		
	7)	
echo "================================================================="
		echo "End of program"
		return 1
		;;	
  esac


}

#-----------Creating temp files and arrays for storing files-----------

# directory named os needs to be created in home/user_name


mc=$(mktemp -d /home/mirko/os/MyComputer.XXX)
mm=$(mktemp -d /home/mirko/os/MyMusic.XXX)
mp=$(mktemp -d /home/mirko/os/MyPictures.XXX)
rb=$(mktemp -d /home/mirko/os/RecycleBin.XXX)
us=$(mktemp -d /home/mirko/os/User.XXX)
st=$(mktemp -d /home/mirko/os/Settings.XXX)

mcFiles=()
mmFiles=()
mpFiles=()
rbFiles=()
usFiles=()
stFiles=()

osFiles=()

osFiles+=(${mc})
osFiles+=(${mm})
osFiles+=(${mp})
osFiles+=(${rb})
osFiles+=(${us})



#--------------------------Starting a program--------------------------
echo "Username:"
read USERNAME


echo "Password:"
read PASSWORD
echo "================================================================="

if [[ $USERNAME = "Lejla" && $PASSWORD = "123" ]]; then
echo "Correct validation"
get_in_home_screen

else 
echo "Access denied"
fi


#------------Deleting temp files at the end of the program-------------

rm -R "$mc"
rm -R "$mm"
rm -R "$mp"
rm -R "$rb"
rm -R "$us"
rm -R "$st"






























