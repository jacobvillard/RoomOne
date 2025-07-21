# RoomOne

RoomOne 🎮

A Multiplayer Chat & Game Framework Built in Unreal Engine 5

Installation •
Features •
Usage •
Demo •
Contributing •
License •
Join our Discord

📖 Overview

RoomOne is a multiplayer framework and demo project built in Unreal Engine 5, featuring a fully networked chat system with color-coded messages per user. It serves as a foundation for experimenting with multiplayer replication, user interface design, and networked player communication.

Whether you're building a social hub or testing core multiplayer systems, RoomOne offers a solid Unreal-native template.

🚀 Features

💬 Networked chat system with sender color-coding

🧝 Unique player identification using dynamic colors

🔁 Server-authoritative message handling with client replication

🔀 Fully Blueprint-based UI and logic

🎮 Expandable with additional gameplay systems (e.g. voice chat, emotes, or player tags)

📦 Installation

Clone the repository

git clone https://github.com/your-org/RoomOne.git
cd RoomOne

Open in Unreal Engine 5

Open RoomOne.uproject

Build missing binaries if prompted

Run the game

Use Play in Editor or run in a packaged build with multiple clients

🧑‍💻 Usage

Messages are sent using a custom AddChatMessageOnOwningClient event

Each message is assigned a sender index and matched to a color

SlateColor is used to apply the correct color in UI per message

The logic for setting message color is executed before replication, ensuring consistency across clients

🎮 Demo

Add screenshots or GIFs of the chat system in action



💪 Contributing

We welcome contributions and suggestions:

Fork this repo

Create your feature branch (git checkout -b feature/YourFeature)

Commit your changes

Push to your branch

Open a Pull Request

Bug reports and feature requests are also welcome via Issues.

📄 License

This project is licensed under the MIT License.

