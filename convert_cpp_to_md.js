const fs = require('fs');
const path = require('path');

// 目标目录：_posts 及其子文件夹
const postsDir = path.join(__dirname, 'source/_posts');

// 递归扫描 CPP 文件
function scanCppFiles(dir) {
  const files = fs.readdirSync(dir, { withFileTypes: true });
  for (const file of files) {
    const fullPath = path.join(dir, file.name);
    if (file.isDirectory()) {
      scanCppFiles(fullPath); // 递归子文件夹
    } else if (file.name.endsWith('.cpp')) {
      convertCppToMd(fullPath); // 转换 CPP 为 MD
    }
  }
}

// 将 CPP 文件转为 MD（代码块形式）
function convertCppToMd(cppPath) {
  // MD 文件路径：和 CPP 同目录，后缀改为 .md
  const mdPath = cppPath.replace('.cpp', '.md');
  
  // 跳过已生成的 MD 文件（避免重复）
  if (fs.existsSync(mdPath)) return;

  // 读取 CPP 内容
  const cppContent = fs.readFileSync(cppPath, 'utf8');
  
  // 生成 MD 内容（带 Front-matter + 代码块）
  const mdContent = `---
title: ${path.basename(cppPath, '.cpp')}
date: ${new Date().toISOString().slice(0, 19).replace('T', ' ')}
categories: ${path.dirname(cppPath).split(postsDir)[1].split(path.sep).filter(Boolean).join(' > ')}
tags: [C++]
---

# ${path.basename(cppPath, '.cpp')}
以下是完整的 C++ 代码：

\`\`\`cpp
${cppContent}
\`\`\`
`;

  // 写入 MD 文件
  fs.writeFileSync(mdPath, mdContent, 'utf8');
  console.log(`已生成 MD 文件：${mdPath}`);
}

// 执行扫描+转换
scanCppFiles(postsDir);
console.log('CPP 转 MD 完成！');