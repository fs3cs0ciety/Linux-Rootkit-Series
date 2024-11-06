/* The master guide thru the Xcellerator rootkit series and it's tweaked to work on the latest kernel version as well. I will have each one individually listed in its own directory in src/ as well as a main-build including all of the hooks put together in one module and wayyyyy more debloated and orginized. As my buddy Humza says DONT EVER WRITE ALL YOUR CODE IN ONE FILE YOU NUMNUT*

1.  HIDING_DIRECTORIES/HIDING_FILES

![hide_dir](https://github.com/user-attachments/assets/c91386e3-23c1-4cfe-adaa-4e5fda61f5f3)

    -- everything with the prefix "x" will be hidden 
    -- #define PREFIX "x" in hooks/getdents.h, you can change "x" to whatever you want. 
    -- touch lol.txt
    -- mv lol.txt x_lol.txt
    -- File will now be hidden from userspace 

---------------------------------------------------------------------------------------------
2.  ROOT SIGNALING && HIDING LKM FROM LSMOD 

![root_hide](https://github.com/user-attachments/assets/785e97d6-0a3c-4034-9ebc-371e708a0085)


    -- kill -64 1 will go and change the id's of the user to 0, meaning you are now root.
    -- kill -33 1 will toggle between hiding and showing the module to /proc/modules list.
    -- when giving root go and run "bash" youll now be root and cd /root etc.
    -- You will not be able to remove this module with toggled hide on.

---------------------------------------------------------------------------------------------

3.  HIDE TCP CONNECTIONS


![hide_tcp](https://github.com/user-attachments/assets/8d4a8dd7-4bd2-4466-aaba-29edb4c5bb07)



-----------------------------------------------------------------------------------------

CREDITS:

https://github.com/xcellerator

