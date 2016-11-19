package main

import (
	"bufio"
	"fmt"
)

func checkfile(file *File) {
	scanner := bufio.NewScanner(file)
	var lines []string
	for scanner.Scan() {
		lines = append(lines, scanner.Text())
	}

}

func column1() {

}

func lable() {

}

func column89() {

}

func endcall() {

}

func checkop() {

}

func main() {
	if file, err := bufio.Open("test1.txt"); err != nil {
		fmt.Println("Error opening file", err)
	}
	defer file.Close()

	checkfile(file)

}
