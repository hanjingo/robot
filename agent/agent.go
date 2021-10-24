package agent

type agent struct {
	info map[interface{}]interface{}
}

func (a *agent) Init(opts map[interface{}]interface{}) {

}

func (a *agent) Info() map[interface{}]interface{} {
	return a.info
}

func (a *agent) Connect(ip string, port int) {

}

func (a *agent) DisConnect() {

}
