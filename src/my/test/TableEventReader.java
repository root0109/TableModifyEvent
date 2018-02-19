package my.test;
import com.rabbitmq.client.Channel;
import com.rabbitmq.client.Connection;
import com.rabbitmq.client.ConnectionFactory;

/**
 * @author vaibhav
 *
 */
public class TableEventReader
{
	// Load native lib
	static
	{
		System.loadLibrary("tme");
	}
	
	// Native declarations
	public static native void read_message(int qid, TableEvent tableEvent, long type);
	public static native int get_message_qid();
	// End of Native declarations
	
	public static TableEventReader instance = new TableEventReader();
	
	private final int eventQueueId;
	
	private volatile boolean isRunning = true;
	
	private TableEventReader()
	{
		eventQueueId = get_message_qid();
		
		new Thread(() ->
		{
			while (isRunning)
			{
				try
				{
					TableEvent tableEvent = new TableEvent();
					read_message(eventQueueId, tableEvent, 1);
					// add this event object to Rabbit MQ
					ConnectionFactory factory = new ConnectionFactory();
					factory.setHost("localhost");
					Connection connection = factory.newConnection();
					Channel channel = connection.createChannel();
					channel.exchangeDeclare("myTopic", "topic");
					channel.basicPublish("myTopic", tableEvent.topic, null, tableEvent.data.getBytes());
					channel.close();
					connection.close();
				}
				catch (Throwable e)
				{
					e.printStackTrace();;
				}
			}
		}).start();
	}
	
	public synchronized void stop()
	{
		if (!isRunning)
			return;
		
		isRunning = false;
	}
	
	public synchronized void start()
	{
		if (isRunning)
			return;
		
		isRunning = true;
	}
}
