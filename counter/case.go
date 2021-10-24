package counter

import (
	"context"
	"sync"
	"time"
)

type epoch struct {
	start_time time.Time
	tfn        int64
	tsn        int64
	art        time.Duration
	max_rt     time.Duration
	min_rt     time.Duration

	mplayer map[interface{}]*trans
	cu      int64
}

func newEpoch() *epoch {
	return &epoch{
		start_time: time.Now(),
		mplayer:    make(map[interface{}]*trans),
	}
}

type cases struct {
	mu         *sync.RWMutex
	updateChan chan bool
	desc       interface{}

	expire time.Duration
	last   *epoch
	curr   *epoch

	brun   bool
	finish context.CancelFunc
}

func newCases(desc interface{}, expire_dur time.Duration) *cases {
	return &cases{
		mu:         new(sync.RWMutex),
		updateChan: make(chan bool, 1),
		desc:       desc,
		expire:     expire_dur,

		curr: newEpoch(),
		brun: false,
	}
}

func (c *cases) info() *CaseInfo {
	c.mu.RLock()
	defer c.mu.RUnlock()

	info := &CaseInfo{}

	return info
}

func (c *cases) run() {
	if c.brun {
		return
	}

	c.brun = true
	go func() {
		for {
			select {
			case <-c.updateChan:
				c.update()
			}
		}
	}()
}

func (c *cases) startTrans(agent interface{}) {
	c.mu.Lock()
	defer c.mu.Unlock()

	now := time.Now()
	t := c.curr.mplayer[agent]
	if t == nil {
		// new player
		t = newTrans()
		c.curr.cu++
	} else {
		// trans expire
		if !t.bfinish {
			if now.Sub(t.start_time) > c.expire {
				// do expire
				c.curr.tfn++
			} else {
				// do unexpire
			}
		}
		t = newTrans()
	}

	c.curr.mplayer[agent] = t
}

func (c *cases) finishTrans(agent interface{}) {
	c.mu.Lock()
	defer c.mu.Unlock()

	now := time.Now()
	t := c.curr.mplayer[agent]
	if t == nil {
		return
	}

	rt := now.Sub(t.start_time)
	if rt > c.expire {
		// time expire
		c.curr.tfn++
		return
	}

	t.finish()
	c.curr.art = (c.curr.art + rt) / 2
	c.curr.tsn++
}

func (c *cases) update() {
	c.mu.Lock()
	defer c.mu.Unlock()

	e := newEpoch()

	// if trans not finished, copy to new epoch
	now := time.Now()
	for k, t := range c.curr.mplayer {
		// expired
		if now.Sub(t.start_time) > c.expire {
			// TODO record expire
			continue
		}
		// if finished, pass
		if t.bfinish {
			continue
		}
		// copy the last
		e.mplayer[k] = t
	}

	c.last = c.curr
	c.curr = e
}
