#include <iostream>
#include <csignal>
#include <chrono>
#include <thread>

volatile std::sig_atomic_t gSignalStatus = 0;

#ifdef __linux__
void signalHandler( int signalNumber ) {
	if (gSignalStatus)
		return;	// already handled
	gSignalStatus = signalNumber;
	using std::cerr; using std::endl;
	cerr << "Interrupt signal received: " << endl;
	// source: http://www.comptechdoc.org/os/linux/programming/linux_pgsignals.html
	switch(gSignalStatus){
		case 1: cerr << "SIGHUP	1	Hangup (POSIX)" << endl; break;
		case 2: cerr << "SIGINT	2	Terminal interrupt (ANSI)" << endl; break;
		case 3: cerr << "SIGQUIT	3	Terminal quit (POSIX)" << endl; break;
		case 4: cerr << "SIGILL	4	Illegal instruction (ANSI)" << endl; break;
		case 5: cerr << "SIGTRAP	5	Trace trap (POSIX)" << endl; break;
		case 6: cerr << "SIGIOT	6	IOT Trap (4.2 BSD)" << endl; break;
		case 7: cerr << "SIGBUS	7	BUS error (4.2 BSD)" << endl; break;
		case 8: cerr << "SIGFPE	8	Floating point exception (ANSI)" << endl; break;
		// can't handle SIGKILL
		case 9: cerr << "SIGKILL	9	Kill(can't be caught or ignored) (POSIX)" << endl; break;
		case 10: cerr << "SIGUSR1	10	User defined signal 1 (POSIX)" << endl; break;
		case 11: cerr << "SIGSEGV	11	Invalid memory segment access (ANSI)" << endl; break;
		case 12: cerr << "SIGUSR2	12	User defined signal 2 (POSIX)" << endl; break;
		case 13: cerr << "SIGPIPE	13	Write on a pipe with no reader, Broken pipe (POSIX)" << endl; break;
		case 14: cerr << "SIGALRM	14	Alarm clock (POSIX)" << endl; break;
		case 15: cerr << "SIGTERM	15	Termination (ANSI)" << endl; break;
		case 16: cerr << "SIGSTKFLT	16	Stack fault" << endl; break;
		case 17: cerr << "SIGCHLD	17	Child process has stopped or exited, changed (POSIX)" << endl; break;
		case 18: cerr << "SIGCONT	18	Continue executing, if stopped (POSIX)" << endl; break;
		case 19: cerr << "SIGSTOP	19	Stop executing(can't be caught or ignored) (POSIX)" << endl; break;
		case 20: cerr << "SIGTSTP	20	Terminal stop signal (POSIX)" << endl; break;
		case 21: cerr << "SIGTTIN	21	Background process trying to read, from TTY (POSIX)" << endl; break;
		case 22: cerr << "SIGTTOU	22	Background process trying to write, to TTY (POSIX)" << endl; break;
		case 23: cerr << "SIGURG	23	Urgent condition on socket (4.2 BSD)" << endl; break;
		case 24: cerr << "SIGXCPU	24	CPU limit exceeded (4.2 BSD)" << endl; break;
		case 25: cerr << "SIGXFSZ	25	File size limit exceeded (4.2 BSD)" << endl; break;
		case 26: cerr << "SIGVTALRM	26	Virtual alarm clock (4.2 BSD)" << endl; break;
		case 27: cerr << "SIGPROF	27	Profiling alarm clock (4.2 BSD)" << endl; break;
		case 28: cerr << "SIGWINCH	28	Window size change (4.3 BSD, Sun)" << endl; break;
		case 29: cerr << "SIGIO	29	I/O now possible (4.2 BSD)" << endl; break;
		// can't handle SIGPWR
		case 30: cerr << "SIGPWR	30	Power failure restart (System V)" << endl; break;
		// can't handle SIGSYS
		case 31: cerr << "SIGSYS	31	Bad System Call" << endl; break;
		default: cerr << "Unknown signal" << endl; break;
		// more signals in realtime versions, see http://www.yolinux.com/TUTORIALS/C++Signals.html
	}
	exit(-1);


}
#elif _WIN32
// will be run asynchronously!
void signalHandler( int signalNumber ) {
	using std::cerr; using std::endl; 
	if (gSignalStatus)
		return;
	gSignalStatus = signalNumber;
	cerr << "Interrupt signal (" << signalNumber << ") received.\n";
	// source: https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/signal
	switch(signalNumber){
		case 6: cerr << "SIGABRT	Abnormal termination" << endl; break;
		case SIGFPE: cerr << "SIGFPE	Floating-point error" << endl; break;
		case SIGILL: cerr << "SIGILL	Illegal instruction" << endl; break;
		// SIGINT not supported for any Win32 application	
		case SIGINT: cerr << "SIGINT	CTRL+C signal" << endl; break;
		case SIGSEGV: cerr << "SIGSEGV	Illegal storage access" << endl; break;
		case SIGTERM: cerr << "SIGTERM	Termination request" << endl; break;
		// What is signal 21? 
		case 21: cerr << "Unknown signal" << endl; break;
		case 22: cerr << "This application has requested the Runtime to terminate it" << endl; break;
		default: cerr << "Unknown signal" << endl; break;
	}
	exit(-1);
}
#else 
void signalHandler( int signalNumber ) {}
#endif
void signalHookup(){
	static bool hooked;
	if (hooked) return;	// already done;
	#ifdef __linux__
		struct sigaction action;
		action.sa_handler = signalHandler;
		sigemptyset (&action.sa_mask);
		action.sa_flags = 0;
		for (int i = 0; i < 30; ++i)
			sigaction (i, &action, NULL);
	#elif _WIN32
		for (int i = 0; i < 30; ++i)	
			std::signal(i, signalHandler);
	#endif
	hooked = true;

}
void evilSignalHandler(){
	static bool hooked;
	if (hooked) return;	// already done;
	for (int i = 0; i < 30; ++i){	
		std::signal(i, SIG_IGN);
	}
	hooked = true;	
}

void sleep(){
	static const unsigned millis = 1000;
	static std::chrono::milliseconds sleepDuration(millis);
	std::this_thread::sleep_for(sleepDuration);
}
void sleepThread(){
	while(true)
		sleep();
}
int main () {
	signalHookup();
	std::cout << "Enter valid signal code or otherwise raise signal." << std::endl;
	std::cout << "Going to sleep... :)" << std::endl;
#ifdef __linux__
	std::thread t(sleepThread);
	t.detach();
	int signal;
	std::cin >> signal;
	std::raise(signal);
#elif _WIN32	// calling signal is undefined behaviour in multithreaded applications
	while(true){
		sleep();
		int signal;
		std::cin >> signal;
		std::raise(signal);
	}
#endif
}