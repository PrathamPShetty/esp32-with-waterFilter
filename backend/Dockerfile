# Use official Node.js image
FROM node:18-alpine

# Create app directory
WORKDIR /app

# Copy package.json first (for caching)
COPY package*.json ./

# Install dependencies
RUN npm install

# Copy all source code
COPY . .

# Expose backend port
EXPOSE 3000

# Start server
CMD ["node", "app.js"]