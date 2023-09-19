import { ALPHABET } from "./config";
import { createHash } from "crypto";

interface MessageManipulationOptions {
  message: string;
  key: string;
  alphabet: string;
}

const encryptMessage = ({
  message,
  key,
  alphabet,
}: MessageManipulationOptions): { encryptedMessage: string; hash: string } => {
  let encryptedMessage = "";

  const hash = createHash("sha256").update(message).digest("hex");

  for (let i = 0; i < message.length; i++) {
    const char = message[i];
    const charIndex = alphabet.indexOf(char.toUpperCase());

    if (charIndex !== -1) {
      const keyIndex = i % key.length;
      const keyChar = key[keyIndex].toUpperCase();
      const keyShift = alphabet.indexOf(keyChar);

      const shiftedIndex =
        (charIndex + keyShift + parseInt(hash[i % hash.length], 16)) %
        alphabet.length;
      const encryptedChar = alphabet[shiftedIndex];
      encryptedMessage += encryptedChar;
    } else {
      encryptedMessage += char;
    }
  }

  return { encryptedMessage, hash };
};

const decryptMessage = ({
  message,
  key,
  alphabet,
  hash,
}: MessageManipulationOptions & { hash: string }): string => {
  let decryptedMessage = "";

  for (let i = 0; i < message.length; i++) {
    const char = message[i];
    const charIndex = alphabet.indexOf(char.toUpperCase());

    if (charIndex !== -1) {
      const keyIndex = i % key.length;
      const keyChar = key[keyIndex].toUpperCase();
      const keyShift = alphabet.indexOf(keyChar);

      const shiftedIndex =
        (charIndex -
          keyShift +
          alphabet.length -
          parseInt(hash[i % hash.length], 16)) %
        alphabet.length;
      const decryptedChar = alphabet[shiftedIndex];
      decryptedMessage += decryptedChar;
    } else {
      decryptedMessage += char;
    }
  }

  return decryptedMessage;
};

const generateAllPossibleKeys = (
  keyLength: number,
  alphabet: string
): string[] => {
  const keys: string[] = [];

  for (let i = 0; i < Math.pow(alphabet.length, keyLength); i++) {
    let key = "";
    let index = i;

    for (let j = 0; j < keyLength; j++) {
      key = alphabet[index % alphabet.length] + key;
      index = Math.floor(index / alphabet.length);
    }

    keys.push(key);
  }

  return keys;
};

interface bruteforceAttackOptions {
  encryptedMessage: string;
  originalMessage: string;
  alphabet: string;
  hash: string;
}

const bruteforceAttack = ({
  encryptedMessage,
  originalMessage,
  alphabet,
  hash,
}: bruteforceAttackOptions): string | null => {
  const possibleKeys = generateAllPossibleKeys(
    encryptedMessage.length,
    alphabet
  );

  for (const key of possibleKeys) {
    const decryptedMessage = decryptMessage({
      message: encryptedMessage,
      key,
      alphabet,
      hash,
    });
    if (decryptedMessage === originalMessage) {
      return decryptedMessage;
    }
  }

  return null;
};

const message = "HELLO";
const key = "KEYKE";

const { encryptedMessage, hash } = encryptMessage({
  message,
  key,
  alphabet: ALPHABET,
});

const decryptedMessage = decryptMessage({
  message: encryptedMessage,
  key,
  alphabet: ALPHABET,
  hash,
});

const crackedMessage = bruteforceAttack({
  encryptedMessage,
  originalMessage: decryptedMessage,
  alphabet: ALPHABET,
  hash,
});

console.log("Encrypted:", encryptedMessage);
console.log("Decrypted:", decryptedMessage);
console.log("Cracked:", crackedMessage, "\n");
