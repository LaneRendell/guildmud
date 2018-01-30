#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* main header file */
#include "mud.h"

void save_player(D_MOBILE *dMob)
{
  if (!dMob)
  {
    return;
  }

  if ( !db_open() )
  {
    return;
  }

  if ( !db_execute("CREATE TABLE IF NOT EXISTS players (id INTEGER PRIMARY KEY, name TEXT NOT NULL UNIQUE, password TEXT NOT NULL, level INTEGER)") )
  {
    return;
  }

  if ( !db_execute("INSERT INTO players (name, password, level) VALUES (%s, %s, %i)", dMob->name, dMob->password, dMob->level) )
  {
    return;
  }

  db_close();
}

D_MOBILE *load_player(char *player)
{
  D_MOBILE *dMob = NULL;

  /* create new mobile data */
  if (StackSize(dmobile_free) <= 0)
  {
    if ((dMob = malloc(sizeof(*dMob))) == NULL)
    {
      bug("Load_player: Cannot allocate memory.");
      abort();
    }
  }
  else
  {
    dMob = (D_MOBILE *) PopStack(dmobile_free);
  }

  clear_mobile(dMob);

  if ( !db_open() )
  {
    abort();
  }

  sqlite3_stmt *stmt = db_prepare("SELECT name, password, level FROM players WHERE name = %s", player);

  if ( stmt == NULL )
  {
    abort();
  }

  if ( db_step(stmt) == SQLITE_ROW ) {
    dMob->name      = strdup((const char*)sqlite3_column_text(stmt, 0));
    dMob->password  = strdup((const char*)sqlite3_column_text(stmt, 1));
    dMob->level     = sqlite3_column_int(stmt, 2);
  }

  if ( db_finalize(stmt) != SQLITE_OK ) {
    bug("Failed to finalize statement: %s", sqlite3_errmsg(db));

    abort();
  }

  db_close();

  return dMob;
}

/*
* This function loads a players profile, and stores
* it in a mobile_data... DO NOT USE THIS DATA FOR
* ANYTHING BUT CHECKING PASSWORDS OR SIMILAR.
*/
D_MOBILE *load_profile(char *player)
{
  D_MOBILE *dMob = NULL;

  /* create new mobile data */
  if (StackSize(dmobile_free) <= 0)
  {
    if ((dMob = malloc(sizeof(*dMob))) == NULL)
    {
      bug("Load_player: Cannot allocate memory.");
      abort();
    }
  }
  else
  {
    dMob = (D_MOBILE *) PopStack(dmobile_free);
  }

  clear_mobile(dMob);

  if ( !db_open() )
  {
    abort();
  }

  sqlite3_stmt *stmt = db_prepare("SELECT name, password FROM players WHERE name = %s", player);

  if ( stmt == NULL )
  {
    abort();
  }

  switch ( db_step(stmt) ) {
    case SQLITE_ROW:
      dMob->name      = strdup((const char*)sqlite3_column_text(stmt, 0));
      dMob->password  = strdup((const char*)sqlite3_column_text(stmt, 1));

      break;
    default:
      dMob = NULL;

      break;
  }

  if ( db_finalize(stmt) != SQLITE_OK ) {
    bug("Failed to finalize statement: %s", sqlite3_errmsg(db));

    abort();
  }

  db_close();

  return dMob;
}
