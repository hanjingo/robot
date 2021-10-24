package counter

import "time"

type trans struct {
	start_time time.Time
	bfinish    bool
}

func newTrans() *trans {
	return &trans{
		start_time: time.Now(),
		bfinish:    false,
	}
}

func (t *trans) finish() bool {
	if t.bfinish {
		return false
	}
	t.bfinish = true
	return true
}
