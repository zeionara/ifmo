package nara.zeio.mail;

import java.util.Properties;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.PasswordAuthentication;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;
import nara.zeio.authorization.AuthorizationDetails;
import nara.zeio.beans.Ponto;

public class Sender{
  public static void sendMessage(AuthorizationDetails authorizationDetails, Ponto ponto){
    Properties props = new Properties();
		props.put("mail.smtp.host", "smtp.gmail.com");
		props.put("mail.smtp.socketFactory.port", "465");
		props.put("mail.smtp.socketFactory.class", "javax.net.ssl.SSLSocketFactory");
		props.put("mail.smtp.auth", "true");
		props.put("mail.smtp.port", "465");

		Session session = Session.getDefaultInstance(props,
			new javax.mail.Authenticator() {
				protected PasswordAuthentication getPasswordAuthentication() {
					return new PasswordAuthentication("zeionara@gmail.com","streskom56");
				}
			});

		try {
			Message message = new MimeMessage(session);
			message.setFrom(new InternetAddress("zeionara@gmail.com"));
			message.setRecipients(Message.RecipientType.TO, InternetAddress.parse(authorizationDetails.getEmail()));
			message.setSubject("Ponto information");
      String messageText = "Dear "+authorizationDetails.getUsername()+", ponto with coordinates x = "+ponto.getX()+" and y = "+ponto.getY()+" when r = "+ponto.getRad();
      if (ponto.getInside()){
        messageText += " is inside the area";
      } else {
        messageText += " is outside the area.";
      }
			message.setText(messageText);
			Transport.send(message);
			System.out.println("Done sending");
		} catch (MessagingException e) {
			throw new RuntimeException(e);
		}
  }
}
