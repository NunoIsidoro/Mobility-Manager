/**
 * @file   utils.h
 * @brief  This file includes utility functions for the system.
 *
 * @author Nuno Fernandes
 * @date   April 2023
 */

#ifndef UTILIS_H
#define UTILIS_H

#pragma once

#include "headers.h"
#include "clients.h"
#include "managers.h"

 /**
  * @brief Handles the login process for clients and managers.
  *
  * @param clients Pointer to the head of the client linked list.
  * @param managers Pointer to the head of the manager linked list.
  * @param loggedClient Double pointer to store the logged client.
  * @param loggedManager Double pointer to store the logged manager.
  */
void Login(ClientNode* clients, ManagerNode* managers, ClientNode** loggedClient, ManagerNode** loggedManager);

#endif  // UTILIS_H
