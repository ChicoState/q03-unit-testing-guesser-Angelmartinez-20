#include "Guesser.h"
#include <string>
using std::string;

/*
  Returns an whole number representing the distance between the guess,
  provided as an argument, and the secret. The distance represents the number
  of characters that would have to be changed at the same location to match
  the other string. When the two strings are identical, the distance is 0,
  but for each letter different, the distance increases by 1. When the
  strings are different lengths, each of the extra characters in the longer
  string also counts as an increase in 1 to the distance, up to the length of
  the secret; in other words, if m_secret has a 10 characters and the guess
  has 100, the distance is 10.
*/
unsigned int Guesser::distance(string guess){
  unsigned int dist = 0;
  string longest, shortest;

  /* init longest and shortest string */
  if (guess.length() > m_secret.length()) {
    longest = guess;
    shortest = m_secret;
  } else {
    longest = m_secret; 
    shortest = guess;    
  }

  /* counts each mismatched characters */
  for (int i = 0; i < shortest[i]; i++) {
    if (shortest[i] != longest[i]) dist++;
  }

  /* adds lenght diffrence between strings */
  dist += (longest.length() - shortest.length());

  /* returns distance */
  if (dist < m_secret.length()) return dist;
  else return m_secret.length();
}

/*
  Constructor requires that the secret phrase is provided its value as
  an argument. This secret will not change for the lifespan of an instance
  of any Guesser object and must have a length of 32 characters or less,
  otherwise, it will be truncated at that length.
*/
Guesser::Guesser(string secret){
  m_secret = secret.substr(0, 32);
}

/*
  Determines and returns whether the provided guess matches the secret
  phrase. However, the function also returns false if the secret is locked,
  which happens if either (or both): 
    (A) there are no remaining guesses allowed
    (B) the function detects brute force, as indicated by a guess that has a
        distance greater than 2 from the secret
  See the remaining() and distance() functions for specifications regarding
  determining how many guesses are remaining and the distance between a guess
  and the secret.
*/
bool Guesser::match(string guess){
  if (m_locked) return false;

  /* resets attempts if correct match */
  if (guess == m_secret) {
    m_remaining = 3;
    return true;
  }
  m_remaining--;  // unsucceful attampt

  /* locks if dist from secret > than 2*/
  if (distance(guess) > 2) {
    m_locked = true;
    return false;
  }
  /* lcoks if no more remaining */
  if(m_remaining == 0) m_locked = true;

  return false;
}

/*
  Returns the number of guesses remaining. A Guesser object allows up to
  three (3) consecutive guesses without a match. If three guesses are made
  without any being a true match, the secret is locked. However, whenever
  an unlocked secret is guessed with a true match, the guesses remaining
  reset to three (3).
*/
unsigned int Guesser::remaining(){
  return m_remaining;
}

