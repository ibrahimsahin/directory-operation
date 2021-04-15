Expected to design and develop a utility program named “dirop” which makes 
some operations  on directories. ‘dirop’gets  option  string  and  directory  path  as  parameters.  The  input 
format is given below:
dirop [OPTIONS] [ARGUMENT] [DIRECTORY PATH]
There will be six different operations. Theseoperations are described below:
List: This  operation  lists  all  subdirectories  of  the  given  directory  recursively.  The  parameter  for  this
operation is “-l”.
Example: dirop -l c:\temp

Search: This operation finds all directories or filesin a directory according to a search pattern and shows 
the full path as a result. The parameter for thisoperation is “-s”with a file/directory name to be searched 
which can include ‘?’ character. Thischaracter representsany letter.
Example: dirop -s exp3.txt c:\
dirop -s exp?.txt c:\
Delete: This operation finds all directories or filesin a directory according to a search pattern and deletes 
them. If a directory is found, all the subdirectories are deleted with the directory. Deleted directories and 
files must  be  displayed  on  the  screen as  a  result. The  parameter  for  this operation  is “-d” with  a 
file/directory name to be deleted.
Example: dirop-d exp3.txt c:\temp
dirop-d temp? c:\
Update: This operation updates the name of all the files and directories in a given directory. The update 
operation is done based on two rules:
 Turkish characters like “ç, ğ, ı, ö, ş, ü” are replaced with similar characters in English like “c, g, i, o, s, u” 
respectively. 
 Space characters (‘’) are replaced with underline (‘_’) characters.
This operation lists last names of the updated files/directories. If the name of a file or directory is not updated, it 
will not be shown in the output. The parameter for thisoperation is “-u”
Example: dirop -uc:\temp\update

USAGE
Suppose thatyou have a file hierarchy as given below. 
| -- <temp>
| | -- <BBM>
| | | --exp 3.txt
| | | --last code.c
| | | --exp 4.txt
| | -- <türkçe sözler>
| | | --hello.dat
| | | --ığdır .exe
| --<windows>
Let’slook at some sample executionsfor the program:
$ dirop -s last exp ?.txt c:\
c:\temp\BBM\exp 3.txt
c:\temp\BBM\exp 4.txt 
2 items found.

$ dirop -s last code.c c:\
c:\temp\BBM\last code.c 
1 item found.
$ dirop –d hello.dat c:\
c:\temp\türkçe sözler\ödev.dat 
1 item deleted.
$ dirop –l c:\temp
<temp>
| -- <BBM>
| | --exp 3.txt
| | --last code.c
| -- <türkçe sözler>
| | --hello.dat
| | --ığdır .exe
$ dirop -u c:\temp
c:\temp\BBM\exp_3.txt
c:\temp\BBM\last_code.c
c:\turkce_sozler
c:\turkce_sozler\hello.dat
c:\turkce_sozler\igdir_.exe
5 items updated.

UNIX system calls.using Following systemcalls functions:
open(), close(), lseek(), read(), fcntl(),write()
stat(), fstat(), lstat(), unlink()utime(), chdir(),
getcwd(), opendir(), readdir(), closedir(),rmdir()
