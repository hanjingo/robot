package counter

import (
	"errors"
	"sync"
	"time"
)

var EpochDuration = time.Duration(1000) * time.Millisecond

var counter *Counter
var once = new(sync.Once)

func Inst() *Counter {
	once.Do(func() {
		counter = &Counter{
			mu:   new(sync.RWMutex),
			m:    make(map[interface{}]*cases),
			brun: false,

			expire: time.Duration(3000) * time.Millisecond,
		}
	})
	return counter
}

type Counter struct {
	mu     *sync.RWMutex
	m      map[interface{}]*cases
	brun   bool
	expire time.Duration
}

func (c *Counter) Run(expire_dur time.Duration) error {
	if c.brun {
		return errors.New("counter already in run")
	}

	c.brun = true
	c.expire = expire_dur
	go func() {
		tm := time.NewTimer(EpochDuration)
		select {
		case <-tm.C:
			c.update()
			tm = time.NewTimer(EpochDuration)
		}
	}()
	return nil
}

func (c *Counter) StartTrans(agent, id interface{}, opts ...interface{}) {
	c.mu.Lock()
	defer c.mu.Unlock()

	cs := c.m[id]
	if cs == nil {
		var desc interface{}
		if len(opts) > 0 {
			desc = opts[0]
		}
		cs = newCases(desc, c.expire)
		cs.run()
		c.m[id] = cs
	}

	cs.startTrans(agent)
}

func (c *Counter) FinishTrans(agent, id interface{}) {
	c.mu.RLock()
	defer c.mu.RUnlock()

	cs := c.m[id]
	if cs == nil {
		return
	}

	cs.finishTrans(agent)
}

func (c *Counter) Info() *CounterInfo {
	info := &CounterInfo{
		Cases: make(map[interface{}]*CaseInfo),
		CPUU:  0,
		MU:    0,
		IO:    0,
		NU:    0,
	}

	for k, cs := range c.m {
		info.Cases[k] = cs.info()
	}

	return info
}

func (c *Counter) update() {
	c.mu.Lock()
	defer c.mu.Unlock()

	// update cases
	for _, cs := range c.m {
		cs.updateChan <- true
	}
}
