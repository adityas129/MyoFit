exports.handler =(event, context) => {


  if (event.session.new){
    console.log("NEW SESSION")
  }
  //new session
  switch (event,request,type) {
    case "LaunchRequest":
      console.log('LAUNCH REQUEST')
      context.succeed
      break;
    case "IntentRequest":
      console.log('INTENT REQUEST')
      break;
    case "SessionEndedRequest":
      console.log('SESSION ENDED REQUEST')
      break;
    default:
    context.fail('INVALID REQUEST TYPE: ${event.request.type}')

  }

    //launch Request
    // Intent request
    // Session ended request
}

buildSpeechletResponse = (outputText, shouldEndSession) => {

  return {
    outputSpeech: {
      type: "PlainText",
      text: outputText
    },
    shouldEndSession: shouldEndSession
  }
//can also put a reprompt text
}

generateResponse = (speechletResponse, sessionAttributes) => {

  return {
    version: "1.0",
    sessionAttributes: sessionAttributes,
    response: speechletResponse
  }

}
