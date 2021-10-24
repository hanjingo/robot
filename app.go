package robot

import (
	"context"
	"errors"
	"sync"
	"time"

	agent "github.com/hanjingo/agent"
	counter "github.com/hanjingo/counter"
)

var app *Application
var once = new(sync.Once)

func App() *Application {
	once.Do(func() {
		app = &Application{
			brun: false,
		}
	})
	return app
}

type Application struct {
	brun   bool
	finish context.CancelFunc
}

func (a *Application) Run(nagent int, epoch time.Duration) error {
	if a.brun {
		return errors.New("application already in run")
	}

	// run counter
	if err := counter.Inst().Run(epoch); err != nil {
		return err
	}

	// init player_mgr
	agent.Mgr().Init(nagent)
}

func (a *Application) Interrupt() error {
	if !a.brun {
		return errors.New("application not run")
	}

	a.brun = false
	// wait for agent mgr full
	go func() {
		cache := agent.Mgr().Cache()
		for !cache.Full() {
			time.Sleep(100) * time.Millisecond
		}
		for agent.Mgr().Size() > 0 {
			a := agent.Mgr().Get()
			a.Disconnect()
		}
	}()
}
