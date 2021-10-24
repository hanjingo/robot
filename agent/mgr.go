package agent

import (
	"sync"
)

var m *mgr
var once = new(sync.Once)

func Mgr() *mgr {
	once.Do(func() {
		m = &mgr{}
	})
	return m
}

type mgr struct {
	cache chan *agent
	capa  int
}

func (m *mgr) Init(capa int) {
	m.cache = make(chan *agent, capa)
	m.capa = capa
}

func (m *mgr) Get() *agent {
	return <-m.cache
}

func (m *mgr) Set(a *agent) {
	m.cache <- a
}

func (m *mgr) Full() bool {
	return len(m.cache) == m.capa
}

func (m *mgr) Cache() chan *agent {
	return m.cache
}
