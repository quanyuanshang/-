package main

type Server struct {
	v string
	ch chan string
}

func(s *Server) Start() {
	for c := range s.ch{
		s.v+= c
	}
}
func MakeServer() *Server {
	return &Server{
		v:  "",
		ch: make(chan string,10),
	}
	
}

type Client struct {
	no int
	ch_list []chan string
}
func(cli *Client) append(s string) {
	wg:=sync.WaitGroup{}
	for _, ch := range cli.ch_list {
		wg.Add(1)
		ch_:=ch
		go func(){
			ch_<- s
		}()
	}
	wg.Wait()// wait for all goroutines to finish
}
func MakeClient(no int, servers []*Server) *Client {
	cli:= &Client{
		no: no,
		ch_list: make([]chan string, 0),
	}
	for _, s := range servers {
		cli.ch_list = append(cli.ch_list, s.ch)
	}
	return cli

}


func main() {
	servers := make([]*Server, 2)
	for i := range servers {
		servers[i] = MakeServer()
		go servers[i].Start() // Start each server in a goroutine
	}

	clients := make([]*Client, 10)
	for i := range clients {
		clients[i] = MakeClient(i, servers)

	}
	//let every client send append request
	wg := sync.WaitGroup{}
	for i, c := range clients {
		wg.Add(1)
		go func() {
			for j := 0; j < 1000; j++ {
				c.append(strconv.Itoa(clients[i_].no))
			}
			wg.Done()
		}
	}
	wg.Wait() // Wait for all clients to finish sending messages
	fmt.Println("server 0 value:", servers[0].v)
	fmt.Println("---------")
	fmt.Println("server 1 value:", servers[1].v)
}