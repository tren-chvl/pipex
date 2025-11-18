#!/bin/bash

# Nettoyage avant chaque run
rm -f outfile infile

echo "=== Test 1 : cat | wc -l ==="
echo -e "hello\nworld" > infile
./pipex infile "cat" "wc -l" outfile
echo "Pipex : $(cat outfile)"
echo "Shell : $(cat < infile | wc -l)"
echo

echo "=== Test 2 : grep 42 | wc -l ==="
echo -e "42\nhello\n42\nworld" > infile
./pipex infile "grep 42" "wc -l" outfile
echo "Pipex : $(cat outfile)"
echo "Shell : $(grep 42 < infile | wc -l)"
echo

echo "=== Test 3 : ls -l | wc -l ==="
touch infile
./pipex infile "ls -l" "wc -l" outfile
echo "Pipex : $(cat outfile)"
echo "Shell : $(ls -l < infile | wc -l)"
echo

echo "=== Test 4 : commande inexistante ==="
echo "hello" > infile
./pipex infile "foobar" "wc -l" outfile
echo "Résultat attendu : erreur 'command not found'"
echo

echo "=== Test 5 : fichier inexistant ==="
./pipex nofile "cat" "wc -l" outfile
echo "Résultat attendu : erreur 'infile: No such file or directory'"
echo

