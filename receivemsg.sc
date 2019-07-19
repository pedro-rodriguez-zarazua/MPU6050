s.boot;
NetAddr.localAddr;
SerialPort.devices;
(
OSCdef(\msg1,
	{
		arg msg;
		"msg1".postln;
		msg[1].postln;
		msg[2].postln;
		msg[3].postln;
		msg[4].postln;
		msg[5].postln;
		msg[6].postln;
},"/msg1");
)
