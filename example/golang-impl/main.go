package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func getSensorData(filename string) ([]int, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, fmt.Errorf("failed to open file: %s", err)
	}
	defer file.Close()
	var sensorData []int
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		sensorValue, err := strconv.Atoi(scanner.Text())
		if err != nil {
			return nil, fmt.Errorf("failed to parse file: %s", err)
		}
		sensorData = append(sensorData, sensorValue)
	}
	if err := scanner.Err(); err != nil {
		return nil, fmt.Errorf("failed to parse file: %w", err)
	}
	return sensorData, nil
}

func main() {
	sensorData, err := getSensorData("sensor.csv")
	if err != nil {
		fmt.Println("Error:", err)
		return
	}
	for i, v := range sensorData {
		fmt.Printf("%d: %d\n", i, v)
	}
}
