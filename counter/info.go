package counter

import "time"

type CaseInfo struct {
	TPS   float32       // transaction per second
	CU    int64         // current user
	TSN   int64         // transaction success num
	TFN   int64         // transaction fail num
	ART   time.Duration // average response time
	MaxRT time.Duration // max response time
	MinRT time.Duration // min response time
}

type CounterInfo struct {
	Cases map[interface{}]*CaseInfo
	CPUU  float32 // CPU usage
	MU    float32 // memory usage
	IO    float32 // Disk Input/Output
	NU    float32 // network usage
}
